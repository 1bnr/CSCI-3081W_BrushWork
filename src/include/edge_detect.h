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

#ifndef SRC_INCLUDE_EDGE_DETECT_H_
#define SRC_INCLUDE_EDGE_DETECT_H_

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
class EdgeDetect {
 public:
  EdgeDetect();
  virtual ~EdgeDetect();

  static void apply_filter(PixelBuffer* p);

};
}  // namespace image_tools
#endif  // SRC_INCLUDE_EDGE_DETECT_H_
