/*******************************************************************************
 * Name            : mia_app.cc
 * Project         : MIA
 * Module          : App
 * Description     : Implementation of MIA
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 12/07/16
 * Original Author : Team 0x07
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include <iostream>
#include "include/mia_cli.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
******************************************************************************/
MiaCli::MiaCli() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
int MiaCli::init_cli(int argc, char ** argv) {
  if (argc == 2 && std::string(argv[1]) == "-h") {
    print_help(argv[1]);
  }
  if (argc == 4 && std::string(argv[2]) == "-compare") {
    // load the files to be compared
    image_tools::PixelBuffer *pixel_buffer1 = load_image(argv[1]);
    image_tools::PixelBuffer *pixel_buffer2 = load_image(argv[argc - 1]);
    if (pixel_buffer1 == NULL || pixel_buffer2 == NULL) {
      return 1;  // return error; one of the files didn't load
    } else {
      // the files loaded successfully
      compare_images(*pixel_buffer1, *pixel_buffer2);
    }
  }
  if (argc >= 4 && std::string(argv[2]) != "-compare") {
    // first argument is always the input file
    std::string file_in =  argv[1];
    // last argument in is always the output file
    std::string file_out = argv[argc - 1];
    std::cout << "image file in = " << file_in << std::endl;
    std::cout << "image file out = " << file_out << std::endl;

    // loading image
    image_tools::PixelBuffer * curr_image;
    image_tools::FileIo * file_io;
    std::string file_suffix = file_in.substr(file_in.find_last_of(".") + 1);
      if (file_suffix.compare("png") == 0) {
        file_io = new image_tools::FileIoPng();
      } else if ((file_suffix.compare("jpg") == 0) ||
             (file_suffix.compare("jpeg") == 0)) {
        file_io = new image_tools::FileIoJpg();
      }
      curr_image = load_image(file_in);

      // applying filters, at least 1 but could possibly be multiple
      for (int i = 2; i < argc; i+=2) {
        if ((i+1) >= argc) {
          break;
        }
        std::string filter = argv[i];
        // deleting the dash in front of filter name
        filter = filter.erase(0, 1);
        float filter_amount = atof(argv[i+1]);
        if (filter == "edge") {
          i = i-1;
        }
        std::cout << "current filter = " << filter << std::endl;
        std::cout << "filter amount = " << filter_amount << std::endl;

        // decide which filter to be applied
        if (filter == "edge") {
          image_tools::EdgeDetect::apply_filter(curr_image);
        }
        if (filter == "quantize") {
          // if using quantize filter the amount must be an int
        //  filter_amount = int(filter_amount);
          image_tools::Quantize::apply_filter(curr_image,
                                             static_cast<int>(filter_amount));
        }
        if (filter == "sharpen") {
          image_tools::Sharpen::apply_filter(curr_image, filter_amount);
        }
        if (filter == "blur") {
          image_tools::Blur::apply_filter(curr_image, filter_amount);
        }
        if (filter == "threshold") {
          image_tools::Threshold::apply_filter(curr_image, filter_amount);
        }
        if (filter == "saturate") {
          image_tools::Saturate::apply_filter(curr_image, filter_amount);
        }
        save_image(curr_image, file_out);
      }
      free(file_io);
    }
  }

void MiaCli::print_help(char *arg) {
  std::cout << "argument passed to MIA = " << arg << std::endl;
  std::cout << "MIA HELP\n"
                "MIA can be run in graphical mode or command-line mode.\n"
                "below are all command-line operations supported:\n"
                "-h\n"
                "-sharpen <float>\n"
                "-edge\n"
                "-threshold <float>\n"
                "-quantize <int>\n"
                "-blur <float>\n"
                "-saturate <float>\n"
                "-channel <float> <float> <float>\n"
                "-compare"
              << std::endl;
}

int MiaCli::compare_images(const image_tools::PixelBuffer &pixel_buffer1,
                   const image_tools::PixelBuffer &pixel_buffer2) {
  // running image buffer comparison
  int image_compare = 1;
  int i1_width = pixel_buffer1.width();
  int i1_height = pixel_buffer1.height();
  int i2_width = pixel_buffer2.width();
  int i2_height = pixel_buffer2.height();
  // easy check, if sizes don't match they cannot be the same image
  if ((i1_width == i2_width) && (i1_height == i2_height)) {
    for (int i = 0; i < i1_width; i++) {
      for (int j = 0; j< i1_height; j++) {
        if ((pixel_buffer1.get_pixel(i, j).red() !=
        pixel_buffer2.get_pixel(i, j).red()) ||
        (pixel_buffer1.get_pixel(i, j).green() !=
        pixel_buffer2.get_pixel(i, j).green()) ||
        (pixel_buffer1.get_pixel(i, j).blue() !=
        pixel_buffer2.get_pixel(i, j).blue())) {
            image_compare = 0;
            break;
        }
      }
    }
  } else {
    image_compare = 0;
  }
  std::cout << image_compare << std::endl;
}

/* load an image into a PixelBuffer, returns pointer to PixelBuffer or NULL */
image_tools::PixelBuffer * MiaCli::load_image(std::string file_name) {
  image_tools::PixelBuffer *image_pointer;
  image_tools::FileIo * file_io;
  std::string file_suffix = file_name.substr(file_name.find_last_of(".") + 1);
  if (file_suffix.compare("png") == 0) {
    file_io = new image_tools::FileIoPng();
  } else if ((file_suffix.compare("jpg") == 0) ||
             (file_suffix.compare("jpeg") == 0)) {
    file_io = new image_tools::FileIoJpg();
  }
  image_pointer = new image_tools::PixelBuffer(file_io->load_image(file_name));
  free(file_io);
  file_io = NULL;
  return image_pointer;
}

/* save a PixelBuffer to either a jpg or png file; destroys pixel_buffer */
void MiaCli::save_image(image_tools::PixelBuffer *pixel_buffer,
                                                       std::string file_name) {
  image_tools::FileIo * file_io;
  std::string file_suffix = file_name.substr(file_name.find_last_of(".") + 1);
  if (file_suffix.compare("png") == 0) {
    file_io = new image_tools::FileIoPng();
  } else if ((file_suffix.compare("jpg") == 0) ||
             (file_suffix.compare("jpeg") == 0)) {
    file_io = new image_tools::FileIoJpg();
  }
  file_io->save_image(*pixel_buffer, file_name);
  free(pixel_buffer);
  pixel_buffer = NULL;
  free(file_io);
  file_io = NULL;
}

}  /* namespace image_tools */
