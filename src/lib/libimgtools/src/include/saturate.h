/*******************************************************************************
 * Name            : saturate.h
 * Project         : Flashphoto
 * Module          : utils
 * Description     : Header file for Saturate class.
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/14/16
 * Original Author : Isaac Schwab
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SATURATE_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SATURATE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "color_data.h"
#include "pixel_buffer.h"

 /*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is the header file for the threshold filter.
 */
class Saturate {
 public:
  Saturate();
  virtual ~Saturate();

  static void apply_filter(PixelBuffer* p, float saturation_amount);
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SATURATE_H_
