/*******************************************************************************
 * Name            : tool.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Tools class.
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 10/05/16
 * Original Author : Isaac Schwab
 *
 ******************************************************************************/

#ifndef INCLUDE_TOOL_H_
#define INCLUDE_TOOL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/base_gfx_app.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include <vector>

 /*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This Tool class is the abstract class for the type Tool.
 * Subtypes of Tool will override and implement some of these functions.
 */
class Tool {
 public:
  // Default constructor for a tool.
  Tool();
  virtual ~Tool();

  // Discussed possible ways to implement draw function with group
  PixelBuffer * Draw(int const x, int const y, PixelBuffer * const p, ColorData const c);
 protected:
   int mask_rows_;
   int mask_cols_;
   std::vector<std::vector<float> > tool_mask_;
 	
};
}  // namespace image_tools
#endif  // INCLUDE_TOOL_H_
