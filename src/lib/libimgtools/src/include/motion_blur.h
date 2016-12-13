/*******************************************************************************
 * Name            : motion_blur.h
 * Project         : Flashphoto
 * Module          : utils
 * Description     : Header file for Motion Blur class.
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/17/16
 * Original Author : Isaac Schwab
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_MOTION_BLUR_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_MOTION_BLUR_H_

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
  * @brief The MotionBlur class is used to apply a motion blur filter to a
  * PixelBuffer object. This is a convolution based filter.
  */
class MotionBlur {
 public:
  MotionBlur();
  virtual ~MotionBlur();

  /**
   * @brief Apply the filter to the PixelBuffer
   * @param p The PixelBuffer that the filter will operate on
   * @param motion_blur_amount a float which determines how much to blur the PixelBuffer
   * @param direction determines which direction the user wants the blur to act in
   */
  static void apply_filter(PixelBuffer* p, float motion_blur_amount,
                           int direction);
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_MOTION_BLUR_H_
