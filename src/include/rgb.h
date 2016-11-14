/*******************************************************************************
 * Name            : rgb.h
 * Project         : Flashphoto
 * Module          : utils
 * Description     : Header file for rgb class.
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/14/16
 * Original Author : Ben Bramanti
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_RBG_H_
#define SRC_INCLUDE_RBG_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/color_data.h"
#include "include/pixel_buffer.h"

 /*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is the header file for the rgb filter.
 */
class RGB {
 public:
  RGB();
  virtual ~RGB();

  void apply_filter(PixelBuffer* p, float red, float blue, float green);

};
}  // namespace image_tools
#endif  // INCLUDE_RGB_H_
