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
  // command line filtering
  if (argc >= 4){
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
        image_tools::Quantize::apply_filter(curr_image,filter_amount);
      }
      if (filter == "threshold"){
        image_tools::Threshold::apply_filter(curr_image,filter_amount);
      }
      if (filter == "saturate"){
        image_tools::Quantize::apply_filter(curr_image,filter_amount);
      }
    file_io->save_image(*curr_image, file_out);
    free(file_io);
  }
}
   else {
    /* Create command line interface */
  }
  return 0;
} /* main() */
