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

#ifndef SRC_APP_MIA_SRC_INCLUDE_MIA_CLI_H_
#define SRC_APP_MIA_SRC_INCLUDE_MIA_CLI_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <math.h>
#include "./mia_app.h"
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
  void print_help(const char *arg);
  int compare_images(const image_tools::PixelBuffer &pixel_buffer1,
                     const image_tools::PixelBuffer &pixel_buffer2);
private:
  int to_int(float in) {return static_cast<int>(floor(1000000 * in));}
  PixelBuffer * load_image(std::string file_name);
  int save_image(image_tools::PixelBuffer *pixel_buffer, std::string filename);
  bool is_int(const char *str);
  bool is_float (const char * str);
};

}  /* namespace image_tools */

#endif  // SRC_APP_MIA_SRC_INCLUDE_MIA_CLI_H_
