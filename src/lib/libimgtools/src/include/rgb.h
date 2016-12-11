/*******************************************************************************
 * Name            : rgb.h
 * Project         : Flashphoto
 * Module          : utils
 * Description     : Header file for rgb class.
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/14/16
 * Original Author : Ben Bramanti
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_RGB_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_RGB_H_

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
  * @brief The RGB class is used to apply an rgb filter to a
  * PixelBuffer object. This is a pixel-independent filter.
  */
class RGB {
 public:
  RGB();
  virtual ~RGB();

  /**
   * @brief Apply the filter to the PixelBuffer
   * @param p The PixelBuffer that the filter will operate on
   * @param red factor that will either increase or decrease the intensity of this channel
   * @param blue factor that will either increase or decrease the intensity of this channel
   * @param green factor that will either increase or decrease the intensity of this channel
   */
  static void apply_filter(PixelBuffer* p, float red, float blue, float green);
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_RGB_H_
