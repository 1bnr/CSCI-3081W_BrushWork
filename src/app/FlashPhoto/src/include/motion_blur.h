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

#ifndef SRC_INCLUDE_MOTION_BLUR_H_
#define SRC_INCLUDE_MOTION_BLUR_H_

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
 * @brief This is the header file for the threshold filter.
 */
class MotionBlur {
 public:
  MotionBlur();
  virtual ~MotionBlur();

  static void apply_filter(PixelBuffer* p, float motion_blur_amount,
                           int direction);
};
}  // namespace image_tools
#endif  // SRC_INCLUDE_MOTION_BLUR_H_
