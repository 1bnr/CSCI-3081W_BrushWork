/*******************************************************************************
 * Name            : mia_app.h
 * Project         : MIA
 * Module          : App
 * Description     : Header file for MIA class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 5/15/15
 * Original Author : Team 0x07
 *
 ******************************************************************************/

#ifndef SRC_APP_MIA_SRC_MIA_CLI_H_
#define SRC_APP_MIA_SRC_MIA_CLI_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
 #include "mia_app.h"
/*******************************************************************************
* Namespaces
******************************************************************************/
namespace image_tools {

/*******************************************************************************
* Class Definitions
******************************************************************************/
/**
* @brief The main class for MIA_CLI.
* It is a command line interface for the MIA medical imaging application
**/
class MiaCli {
 public:
  MiaCli();
  ~MiaCli() {}
  int init_cli(int argc, char **argv);
  void print_help(char *arg);
  PixelBuffer * load_image(std::string file_name);
  int compare_images(const image_tools::PixelBuffer &pixel_buffer1,
                     const image_tools::PixelBuffer &pixel_buffer2);
void save_image(image_tools::PixelBuffer *pixel_buffer, std::string file_name);
};

}  /* namespace image_tools */

#endif  // SRC_APP_MIA_SRC_MIA_CLI_H_
