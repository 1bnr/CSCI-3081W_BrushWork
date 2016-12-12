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
#include <math.h>
#include <string>
#include <list>
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
  /**
   * @brief initialize the command line interface to recieve commands.
   * commands are passed through from the command line when MIA is launced
   * @return 0 on success, otherwise 1
   */
  int init_cli(int argc, char **argv);
  /**
   * @brief print a instructional message to stdout
   * @param arg string for displaying last command entered in case of error
   * @return 0 on success, otherwise 1
   */
  void print_help(std::string arg);
  /**
   * @brief compare two images, pixel by pixel
   * @param pixel_buffer1 the PixelBuffer representation of the first image
   * @param pixel_buffer2 the PixelBuffer representation of the second image
   * @return 1 if images are identical, otherwise 0
   */
  int compare_images(const image_tools::PixelBuffer &pixel_buffer1,
                     const image_tools::PixelBuffer &pixel_buffer2);
 private:
  /// @brief a std::list of std::string tuples of filter name and filter arg
  std::list<std::string[2]> jobs_;
  /// @brief convert a float into an int for camparison purposes
  int to_int(float in) {return static_cast<int>(floor(1000000 * in));}
  /**
   * @brief process the list of operations in jobs_
   * @param file_name1 string containing path to input file
   * @param file_name2 string containing path to second file;
   *  the second file is for output, except in the case of the compare command
   * @return 0 on success, otherwise 1
   */
  int process_jobs(std::string file_name1, std::string file_name2);
  /**
   * @brief load the image file at the path specified
   * @param file_name a string containing the path and name to the file to be
   * opened.
   * @return a PixelBuffer containing the image data on success, otherwise an
   * empty, 0 x 0 sized PixelBuffer.
   */
  PixelBuffer * load_image(std::string file_name);
  /**
   * @brief save an image to the path specified in string file_name
   * @param pixel_buffer a pointer to a PixelBuffer representation of image
   * @param filename a string containing path and name of the output
   * @return 0 on success, otherwise 1
   */
  int save_image(image_tools::PixelBuffer *pixel_buffer, std::string filename);
};

}  /* namespace image_tools */

#endif  // SRC_APP_MIA_SRC_INCLUDE_MIA_CLI_H_
