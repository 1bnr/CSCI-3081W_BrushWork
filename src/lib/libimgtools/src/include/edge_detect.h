/*******************************************************************************
 * Name            : edge_detect.h
 * Project         : Flashphoto
 * Module          : utils
 * Description     : Header file for Edge Detect class.
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/16/16
 * Original Author : Ben Bramanti
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EDGE_DETECT_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EDGE_DETECT_H_

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
 * @brief The EdgeDetect class is used to apply an edge detect filter to a 
 * PixelBuffer object. This is a convolution based filter.
 */
class EdgeDetect {
 public:
  EdgeDetect();
  virtual ~EdgeDetect();

  /**
   * @brief Apply the filter to the PixelBuffer
   * @param p The PixelBuffer that the filter will operate on
   */
  static void apply_filter(PixelBuffer* p);
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EDGE_DETECT_H_
