/*******************************************************************************
 * Name            : highlighter.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Calligraphy Pen class.
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 10/09/16
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

#ifndef INCLUDE_HIGHLIGHTER_H_
#define INCLUDE_HIGHLIGHTER_H_

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
 * @brief This is the header file for the calligrahy pen tool.
 */
class Highlighter : public Tool {
 public:
  Highlighter();
  virtual ~Highlighter();
};
}  // namespace image_tools
#endif  // INCLUDE_HIGHLIGHTER_H_
