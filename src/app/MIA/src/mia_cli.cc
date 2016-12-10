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
#include <string>
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
    if (pixel_buffer1 == NULL) {
      std::cout << "coulding load image: " << argv[1] << std::endl;
      print_help(argv[1]);
      return 1;  // return error; one of the files didn't load
    } else if (pixel_buffer2 == NULL) {
      std::cout << "coulding load image: " << argv[argc - 1] << std::endl;
      print_help(argv[argc - 1]);
      return 1;  // return error; one of the files didn't load
    } else {
      // the files loaded successfully
      if (compare_images(*pixel_buffer1, *pixel_buffer2)) {
        std::cout << "the images " << argv[1] << " and " << argv[argc - 1];
        std::cout << " are pixel-to-pixel identical\n";
      } else {
          std::cout << "the images " << argv[1] << " and " << argv[argc - 1];
          std::cout << " are not identical\n";
      }
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
        // if string 'filter' doesn't have a dash, it isn't a filter
        if ('-' != filter.at(0)) {
          std::cout << "Error! '" << filter << "' is not a valid command\n";
          print_help(filter.c_str());
          return 1;
        }

        // deleting the dash in front of filter name
        filter = filter.erase(0, 1);
        // capture float or int argument
        float float_arg;
        int int_arg;
        int foundint, foundfloat;
        foundfloat = sscanf(argv[i+1], "%f", &float_arg);
        foundint= sscanf(argv[i+1], "%d", &int_arg);

        fprintf(stderr, "foundfloat %d\n",foundfloat );
        fprintf(stderr, "foundint %d\n",foundint );

        if (filter == "edge") {
          i = i-1; // edge takes only one argument, the ouput file name
        }
        else if (!(foundint || foundfloat)) {
          std::cout << "Error! '" << argv[i+1];
          std::cout << "'is not valid input for -" << filter << std::endl;
          print_help(argv[i+1]);
          return 1;
        }
        std::cout << "current filter = " << filter << std::endl;
        std::cout << "filter amount = " << argv[i+1] << std::endl;

        // decide which filter to be applied
        if (filter == "edge") {
          image_tools::EdgeDetect::apply_filter(curr_image);
        }

        if (filter == "quantize") {
          // if using quantize filter the amount must be an int
          if (foundint)
            image_tools::Quantize::apply_filter(curr_image, int_arg);
          else {
            std::cout << "Error! '" << argv[i+1];
            std::cout << "'is not valid input for -" << filter << std::endl;
            print_help(argv[i+1]);
            return 1;
          }
        }
        if (foundint && !foundfloat)
          float_arg = static_cast<float>(int_arg);
        if (filter == "sharpen") {
          image_tools::Sharpen::apply_filter(curr_image, float_arg);
        }
        if (filter == "blur") {
          image_tools::Blur::apply_filter(curr_image, float_arg);
        }
        if (filter == "threshold") {
          image_tools::Threshold::apply_filter(curr_image, float_arg);
        }
        if (filter == "saturate") {
          image_tools::Saturate::apply_filter(curr_image, float_arg);
        }
        if (save_image(curr_image, file_out)) {
          // save image failure
          std::cout << "Error! '" << file_out << "' is not a valid file name.\n";
          print_help(file_out.c_str());
          return 1;
        }
      }
      free(file_io);
    }
  }

void MiaCli::print_help(const char *arg) {
  std::cout << "argument passed to MIA = " << arg << std::endl;
  std::cout << "MIA HELP\n"
  "MIA can be run in graphical mode or command-line mode.\n"
  "below are all command-line operations supported:\n"
  "+------------------------+-----------------------------------------------+\n"
  "|   command              |               brief description               |\n"
  "+------------------------+-----------------------------------------------+\n"
  "-h                        this help message\n"
  "-sharpen <float>          sharpen image proportional to <float>\n"
  "-edge                     edge detection filter\n"
  "-threshold <float>        threshold filter; <float> range [0.0-1.0] \n"
  "-quantize <int>           reduce number of colors by 'binning' each value\n"
  "-blur <float>             blur image proportional to <float>\n"
  "-saturate <float>         alter color saturation by <float> value\n"
  "-compare                  a pixel-by-pixel comparison with filename2\n\n"
  "Usage:\n\n\tbuild/bin/MIA <filename1> "
  "[< -command1 [com1_arg] > ... ] <filename2>\n\n"
  "unless otherwise noted, filename1 is the input and filename2 is the output.";
  std::cout << std::endl;
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
        // fetch the two pixels to be compared
        ColorData pixel1 = pixel_buffer1.get_pixel(i, j);
        ColorData pixel2 = pixel_buffer2.get_pixel(i, j);
        if ((to_int(pixel1.red())   != to_int(pixel2.red())) ||
            (to_int(pixel1.green()) != to_int(pixel2.green())) ||
            (to_int(pixel1.blue())  != to_int(pixel2.blue()))) {
          image_compare = 0;
          break;
        }
      }
    }
  } else { // dimensions didn't match
    image_compare = 0;
  }
  std::cout << image_compare << std::endl;
  return image_compare;
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
  else
    return NULL; // not an image file name
  image_pointer = new image_tools::PixelBuffer(file_io->load_image(file_name));
  free(file_io);
  file_io = NULL;
  return image_pointer;
}

/* save a PixelBuffer to either a jpg or png file; destroys pixel_buffer */
int MiaCli::save_image(image_tools::PixelBuffer *pixel_buffer,
                                                       std::string file_name) {
  image_tools::FileIo * file_io = NULL;
  std::string file_suffix = file_name.substr(file_name.find_last_of(".") + 1);
  if (file_suffix.compare("png") == 0) {
    file_io = new image_tools::FileIoPng();
  } else if ((file_suffix.compare("jpg") == 0) ||
             (file_suffix.compare("jpeg") == 0)) {
    file_io = new image_tools::FileIoJpg();
  }
  if (file_io) {
    file_io->save_image(*pixel_buffer, file_name);
    free(file_io);
    file_io = NULL;
    free(pixel_buffer); // image saved to file, destoy buffer
    pixel_buffer = NULL;
    return 0;
  } else {
    // not a valid ouput type, file not saved
    free(pixel_buffer); // image saved to file, destoy buffer
    pixel_buffer = NULL;
    return 1;
  }

}
}  /* namespace image_tools */
