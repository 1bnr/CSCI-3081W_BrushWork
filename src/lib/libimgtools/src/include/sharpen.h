/*******************************************************************************
 * Name            : sharpen.h
 * Project         : Flashphoto
 * Module          : utils
 * Description     : Header file for Sharpen class.
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/17/16
 * Original Author : Isaac Schwab
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SHARPEN_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SHARPEN_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

 /*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The Sharpen class is used to apply a sharpen filter to a
 * PixelBuffer object. This is a convolution based filter.
 */
class Sharpen {
 public:
  Sharpen();
  virtual ~Sharpen();

  /**
   * @brief Apply the filter to the PixelBuffer
   * @param p The PixelBuffer that the filter will operate on
   * @param sharpen_amount determines the amount to sharpen the image
   */
  static void apply_filter(PixelBuffer* p, float sharpen_amount);
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SHARPEN_H_
