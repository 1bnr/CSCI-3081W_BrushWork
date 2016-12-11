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

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_THRESHOLD_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_THRESHOLD_H_

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
  * @brief The Threshold class is used to apply a threshold filter to a
  * PixelBuffer object. This is a pixel-independent filter.
  */
class Threshold {
 public:
  Threshold();
  virtual ~Threshold();

  /**
   * @brief Apply the filter to the PixelBuffer
   * @param p The PixelBuffer that the filter will operate on
   * @param thesh_amount color channels above this number will go to 1.0, below will go to 0.0

   */
  static void apply_filter(PixelBuffer* p, float thresh_amount);
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_THRESHOLD_H_
