/*******************************************************************************
 * Name            : spray_can.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Pen class.
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 10/09/16
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

#ifndef INCLUDE_SPRAY_CAN_H_
#define INCLUDE_SPRAY_CAN_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/base_gfx_app.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include "include/tool.h"

 /*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is the header file for the pen tool.
 */
class SprayCan : public Tool {
 public:
  SprayCan();
  virtual ~SprayCan();
  void Draw(int x, int y, PixelBuffer *p, ColorData const c) {
    Tool::Draw(x, y, p, c);
  }
};
}  // namespace image_tools
#endif  // INCLUDE_SPRAY_CAN_H_
