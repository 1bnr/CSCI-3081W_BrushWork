/*******************************************************************************
 * Name            : quantize.h
 * Project         : Flashphoto
 * Module          : utils
 * Description     : Header file for Quantize class.
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/15/16
 * Original Author : Ben Bramanti
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_QUANTIZE_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_QUANTIZE_H_

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
  * @brief The Quantize class is used to apply a quantize filter to a
  * PixelBuffer object. This is a pixel-independent filter.
  */
class Quantize {
 public:
  Quantize();
  virtual ~Quantize();

  /**
   * @brief Apply the filter to the PixelBuffer
   * @param p The PixelBuffer that the filter will operate on
   * @param buckets the number of buckets used to quantize the PixelBuffer
   */
  static void apply_filter(PixelBuffer* p, int buckets);
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_QUANTIZE_H_
