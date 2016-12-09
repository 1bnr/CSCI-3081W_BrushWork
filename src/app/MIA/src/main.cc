/*******************************************************************************
 * Name            : main.cc
 * Project         : MIA
 * Module          : main
 * Description     : Entry point for MIA application
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 1/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "mia_app.h"
#include "../../../lib/libimgtools/src/include/color_data.h"
#include <iostream>
#include <stdlib.h>

/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(int argc, char** argv) {
  // mia graphical mode
  if (argc == 1) {
    image_tools::MIAApp *app = new image_tools::MIAApp(
        400,
        400,
        "resources/marker.png");
    app->Init(argc, argv, 50, 50,
              image_tools::ColorData(1, 1, static_cast<float>(0.95)));
    app->RunMainLoop();
    delete app;
  }

  // command line help
  if (argc == 2 && std::string(argv[1]) == "-h"){
    std::cout << "argument passed to MIA = " << argv[1] << std::endl;
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

  // command line image comparison
  if (argc == 4 && std::string(argv[2]) == "-compare"){
    std::string file_1 =  argv[1]; // first argument is always the first file
    std::string file_2 = argv[argc - 1]; // last argument is always the last file

    // loading file_1
    image_tools::PixelBuffer * image_1;
    image_tools::FileIo * file_io;
    std::string file_suffix = file_1.substr(file_1.find_last_of(".") + 1);
    if (file_suffix.compare("png") == 0) {
      file_io = new image_tools::FileIoPng();
    } else if ((file_suffix.compare("jpg") == 0) ||
               (file_suffix.compare("jpeg") == 0)) {
      file_io = new image_tools::FileIoJpg();
    }
    image_1 = new image_tools::PixelBuffer(file_io->load_image(file_1));
    // dimensions needed to compare size of images
    int i1_width = image_1->width();
    int i1_height = image_1->height();

    // loading file_2
    image_tools::PixelBuffer * image_2;
    image_tools::FileIo * file_io2;
    std::string file_suffix2 = file_2.substr(file_2.find_last_of(".") + 1);
    if (file_suffix2.compare("png") == 0) {
      file_io2 = new image_tools::FileIoPng();
    } else if ((file_suffix2.compare("jpg") == 0) ||
               (file_suffix2.compare("jpeg") == 0)) {
      file_io2 = new image_tools::FileIoJpg();
    }
    image_2 = new image_tools::PixelBuffer(file_io2->load_image(file_2));
    // dimensions needed to compare size of images
    int i2_width = image_2->width();
    int i2_height = image_2->height();

    free(file_io);
    free(file_io2);

    // running image comparison
    int image_compare = 1;
    // easy check, if sizes don't match they cannot be the same image
    if ((i1_width == i2_width) && (i1_height == i2_height)){
      for (int i = 0; i < i1_width; i++){
        for (int j = 0; j< i1_height; j++){
            float pix_1_red = image_1->get_pixel(i,j).red();
            float pix_1_green = image_1->get_pixel(i,j).green();
            float pix_1_blue = image_1->get_pixel(i,j).blue();
            float pix_2_red = image_2->get_pixel(i,j).red();
            float pix_2_green = image_2->get_pixel(i,j).green();
            float pix_2_blue = image_2->get_pixel(i,j).blue();
            if ((pix_1_red != pix_2_red) || (pix_1_green != pix_2_green) || (pix_1_blue != pix_2_blue)){
              image_compare = 0;
              break;
            }
        }
      }
  }else{
    image_compare = 0;
    }
    std::cout << image_compare << std::endl;
  }

  // command line filtering
  if (argc >= 4 && std::string(argv[2]) != "-compare"){
    std::string file_in =  argv[1]; // first argument is always the input file
    std::string file_out = argv[argc - 1]; // last argument in is always the output file
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
    curr_image = new image_tools::PixelBuffer(file_io->load_image(file_in));

    // applying filters, at least 1 but could possibly be multiple
    for (int i = 2; i < argc; i+=2){
      if ((i+1) >= argc){
        break;
      }
      std::string filter = argv[i];
      filter = filter.erase(0,1); // deleting the dash in front of filter name
      float filter_amount = atof(argv[i+1]);
      std::cout << "current filter = " << filter << std::endl;
      std::cout << "filter amount = " << filter_amount << std::endl;

      // decide which filter to be applied
      if (filter == "edge"){
        image_tools::EdgeDetect::apply_filter(curr_image);
      }
      if (filter == "quantize"){
        // if using quantize filter the amount must be an int
        filter_amount = int(filter_amount);
        image_tools::Quantize::apply_filter(curr_image,filter_amount);
      }
      if (filter == "sharpen"){
        image_tools::Sharpen::apply_filter(curr_image,filter_amount);
      }
      if (filter == "blur"){
        image_tools::Blur::apply_filter(curr_image,filter_amount);
      }
      if (filter == "threshold"){
        image_tools::Threshold::apply_filter(curr_image,filter_amount);
      }
      if (filter == "saturate"){
        image_tools::Saturate::apply_filter(curr_image,filter_amount);
      }
    file_io->save_image(*curr_image, file_out);
    free(file_io);
  }
}
  return 0;
} /* main() */
