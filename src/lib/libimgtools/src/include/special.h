/*******************************************************************************
 * Name            : special.h
 * Project         : Flashphoto
 * Module          : utils
 * Description     : Header file for Special class.
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/18/16
 * Original Author : Ben Bramanti
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SPECIAL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SPECIAL_H_

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
 * @brief The Special class is used to apply a custom emboss filter to a
 * PixelBuffer object. This is a convolution based filter.
 */
class Special {
 public:
  Special();
  virtual ~Special();

  /**
   * @brief Apply the filter to the PixelBuffer
   * @param p The PixelBuffer that the filter will operate on
   */
  static void apply_filter(PixelBuffer* p);
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SPECIAL_H_
