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
#include <list>
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
  } else {
    std::string filename1 = std::string(argv[1]);
    std::string filename2 = std::string(argv[argc - 1]);
    int arg_count = 2;
    while (arg_count < (argc - 1)) {
      std::string newjob[2];
      newjob[0] = std::string(argv[arg_count++]);
      newjob[1] = (newjob[0] == "-compare" ||
                   newjob[0] == "-edge") ? "" : std::string(argv[arg_count++]);
      jobs_.push_back(newjob);
    }
    // if filenames contain wildcards
    int wc_width = 0;
    int wc_pos1 = 0;
    int wc_pos2 =0;
    unsigned wc_check = filename2.find("#");
    if (wc_check != (-1)) {
      wc_width = filename2.find_last_of("#") - filename2.find_first_of("#") + 1;
      wc_pos1 = filename1.find_first_of("#");
      wc_pos2 = filename2.find_first_of("#");

      char format_pattern[5];
      sprintf(format_pattern, "%%0%dd", wc_width);
      char num[10];
      /* process jobs for wildcard image names */
      for (int i = 0; i < ((10^4)-1); i++) {
        sprintf(num, format_pattern, i);
        process_jobs(filename1.replace(wc_pos1, wc_width, num),
                     filename2.replace(wc_pos2, wc_width, num));
      }
    } else { // no wildcards in names
      process_jobs(filename1, filename2);
    }
  }
}
/* process the jobs_ list for the supplied image names */
int MiaCli::process_jobs(std::string file_name1, std::string file_name2) {
  image_tools::PixelBuffer * image1 = load_image(file_name1);
  image_tools::PixelBuffer * image2;
  if (!image1->width() || !image1->height()) {
    // image1 failed to load_image
    std::cout << "couldn't load image1: " << file_name1 << std::endl;
    print_help(file_name1);
    return 1;
  }
  // passthrough/copy if jobs_ is empty
  if (jobs_.empty()) {
    if(save_image(image2, file_name2)) {
        // save image failure
        std::cout << "Error! '" << file_name2;
        std::cout << "' is not a valid file name. Failed to save image.\n";
        print_help(file_name2);
        return 1;
    }
  } else
  // there are jobs_ to process;
  for (  std::list<std::string[2]>::iterator jit = MiaCli::jobs_.begin(); jit != MiaCli::jobs_.end(); ++jit) {
    if (!(*jit)[0].compare("-compare")) {
      // load the files to be compared
      image2 = load_image(file_name2); // check if it loaded
      if (!image2->width() || !image2->height()) {
        std::cout << "couldn't load image2: " << file_name2 << std::endl;
        print_help(file_name2);
        return 1;  // return error; one of the files didn't load
      } else {
        // the file loaded successfully
          std::cout << "the images " << file_name1 << " and " << file_name2;
        if (compare_images(*image1, *image2)) {
          std::cout << " are pixel-to-pixel identical\n";
        } else {
            std::cout << " are different\n";
        }
      }
    } else  // other filters
      if ((*jit)[0] == "-edge" || (*jit)[0] == "-quantize" ||
          (*jit)[0] == "-sharpen" || (*jit)[0] == "-blur" ||
          (*jit)[0] == "-saturate" || (*jit)[0] == "-threshold") {
        // these commands all produce output
        std::string filter = (*jit)[0];
        // deleting the dash in front of filter name
        filter = filter.erase(0, 1);
        // capture float or int argument
        float float_arg = 0.0;
        int int_arg = 0;
        int foundint = 0;
        int foundfloat = 0;
        if ((*jit)[1].find(".") == -1) // if no decimal point present
          foundint= sscanf((*jit)[1].c_str(), "%d", &int_arg);
        else
          foundfloat = sscanf((*jit)[1].c_str(), "%f", &float_arg);

        std::cout << "current filter = " << filter << std::endl;
        std::cout << "filter amount = " << ((foundfloat) ? float_arg : int_arg);
        std::cout << std::endl;

        // decide which filter to be applied
        if (filter == "edge") {
          image_tools::EdgeDetect::apply_filter(image1);
        }

        if (filter == "quantize") {
          // if using quantize filter the amount must be an int
          if (foundint)
            image_tools::Quantize::apply_filter(image1, int_arg);
          else {
            std::cout << "Error! '" << (*jit)[0];
            std::cout << "'is not valid input for -" << filter << std::endl;
            print_help((*jit)[0]);
            return 1;
          }
        }
        if (foundint && !foundfloat)
          float_arg = static_cast<float>(int_arg);
        if (filter == "sharpen") {
          image_tools::Sharpen::apply_filter(image1, float_arg);
        }
        if (filter == "blur") {
          image_tools::Blur::apply_filter(image1, float_arg);
        }
        if (filter == "threshold") {
          image_tools::Threshold::apply_filter(image1, float_arg);
        }
        if (filter == "saturate") {
          image_tools::Saturate::apply_filter(image1, float_arg);
        }
      }
      else {
        std::string filter = std::string((*jit)[0]);
        std::cout << "Error! " << filter << " is not a valid command.\n";
        print_help(filter);
        return 1;
      }
    }
    if (save_image(image1, file_name2)) {
      // save image failure
      std::cout << "Error! '" << file_name2;
      std::cout << "' is not a valid file name. Failed to save file.\n";
      print_help(file_name2);
      return 1;
    }
    return 0;
  }

void MiaCli::print_help(std::string arg) {
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
  "-compare                  a pixel-by-pixel comparison with image2\n\n"
  "Usage:\n\n\tbuild/bin/MIA <image1> "
  "[< -command1 [com1_arg] > ... ] <image2>\n\n"
  "unless otherwise noted, image1 is the input and image2 is the output.";
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
    int error = 0;
    error = file_io->save_image(*pixel_buffer, file_name);
    free(file_io);
    file_io = NULL;
    free(pixel_buffer); // image saved to file, destoy buffer
    pixel_buffer = NULL;
    return error;
  } else {
    // not a valid ouput type, file not saved
    free(pixel_buffer); // image saved to file, destoy buffer
    pixel_buffer = NULL;
    return 1;
  }

}
}  /* namespace image_tools */
