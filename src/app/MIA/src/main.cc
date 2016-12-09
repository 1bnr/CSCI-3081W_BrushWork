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
   else {
    /* Create command line interface */
  }
  return 0;
} /* main() */
