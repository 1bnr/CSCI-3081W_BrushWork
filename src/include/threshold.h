/*******************************************************************************
 * Name            : threshold.h
 * Project         : Flashphoto
 * Module          : utils
 * Description     : Header file for Threshold class.
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/12/16
 * Original Author : Ben Bramanti
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_THRESHOLD_H_
#define SRC_INCLUDE_THRESHOLD_H_

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
class Threshold {
 public:
  Threshold();
  virtual ~Threshold();

  static void apply_filter(PixelBuffer* p, float thresh_amount);
};
}  // namespace image_tools
#endif  // INCLUDE_THRESHOLD_H_
