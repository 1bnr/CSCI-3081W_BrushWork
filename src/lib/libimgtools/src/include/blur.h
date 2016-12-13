/*******************************************************************************
 * Name            : blur.h
 * Project         : Flashphoto
 * Module          : utils
 * Description     : Header file for Blur class.
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/16/16
 * Original Author : Isaac Schwab
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_BLUR_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_BLUR_H_

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
 * @brief The Blur class is used to apply a blur filter to a 
 * PixelBuffer object. This is a convolution based filter. The filter takes in 
 * a parameter blur_amount, that determines the amount to blur the image.
 */
class Blur {
 public:
  Blur();
  virtual ~Blur();

  /**
   * @brief Apply the filter to the PixelBuffer
   * @param p The PixelBuffer that the filter will operate on
   * @param blur_amount The amount to blur the image
   */
  static void apply_filter(PixelBuffer* p, float blur_amount);
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_BLUR_H_
