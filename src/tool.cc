/*******************************************************************************
 * Name            : tool.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Tool class
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 10/05/16
 * Original Author : Isaac Schwab
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/tool.h"
#include <cmath>
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Tool::Tool() {
}

Tool::~Tool() {}

// The Draw fucntion, take in a color object & the pointer to display buffer
void Tool::Draw(int x, int y, PixelBuffer *p, ColorData c) {
  // adjust the y mouse-parameter to the canvas orientation
  y = p->height() - y;
  //borders for the application
  int window_width = p->width();
  int window_height = p->height();
  // set the start and end positions of the draw mask
  int xpos_start = x - mask_cols_/2;
  int ypos_start = y - mask_rows_/2;

  // filter the pixel data from the canvas and the tool through the mask, and
  // apply them to the canvas
  for (int p_y = 0; p_y < mask_rows_; p_y++) {
    for (int p_x = 0; p_x < mask_cols_; p_x++) {
      
      
      // set the current pixel to the display buffer that we passed in
      // Check that we do not draw outside the border of the application
      if((p_x + xpos_start) >= 0 && (p_x + xpos_start) < window_width &&
        (p_y + ypos_start) >= 0 && (p_y + ypos_start) < window_height) {
        ColorData canvas_pixel = p->get_pixel(xpos_start + p_x, ypos_start + p_y);
        float intensity = static_cast<float>(tool_mask_[p_y][p_x]);
        if (uses_luminance_)
          intensity *= canvas_pixel.luminance();
        float canvas_filter = 1.0 - tool_mask_[p_y][p_x];
        float mask_filter = static_cast<float>(tool_mask_[p_y][p_x]);

        // print out the mask; for debugging
        // std::cout << tool_mask_[p_x][p_y] << ":";
        ColorData new_pixel = (canvas_pixel * canvas_filter) + (c * mask_filter);
        p->set_pixel(p_x + xpos_start, p_y + ypos_start, new_pixel);
      }
        
        

      
    }
    // skip to next line of mask for printout
    // std::cout << std::endl;
  }
// space between filter printouts
// std::cout << std::endl;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

}  // namespace image_tools
