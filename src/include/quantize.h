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

#ifndef SRC_INCLUDE_QUANTIZE_H_
#define SRC_INCLUDE_QUANTIZE_H_

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
 * @brief This is the header file for the quantize filter.
 */
class Quantize {
 public:
  Quantize();
  virtual ~Quantize();

  static void apply_filter(PixelBuffer* p, int buckets);

};
}  // namespace image_tools
#endif  // INCLUDE_QUANTIZE_H_
