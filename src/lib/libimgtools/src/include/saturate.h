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
  * @brief The Saturate class is used to apply a saturate filter to a
  * PixelBuffer object. This is a pixel-independent filter.
  */
class Saturate {
 public:
  Saturate();
  virtual ~Saturate();

  /**
   * @brief Apply the filter to the PixelBuffer
   * @param p The PixelBuffer that the filter will operate on
   * @param saturation_amount float that determines what level of saturation will be used on the PixelBuffer
   */
  static void apply_filter(PixelBuffer* p, float saturation_amount);
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SATURATE_H_
