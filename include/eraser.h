/*******************************************************************************
 * Name            : eraser.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Eraser class.
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 10/05/16
 * Original Author : Ben Bramanti
 *
 ******************************************************************************/

#ifndef INCLUDE_ERASER_H_
#define INCLUDE_ERASER_H_

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
 * @brief This is the header file for the eraser tool.
 * eraser must have a member variable that stores background color.
 */
 class Eraser : public Tool {
  public:
   Eraser();
   virtual ~Eraser();
   virtual void Draw(int x, int y, PixelBuffer *p, ColorData c) { 
      Tool::Draw(x, y, p, c); 
   }
 };
}  // namespace image_tools
#endif  // INCLUDE_ERASER_H_
