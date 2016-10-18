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
void Tool::Draw(int x, int y, PixelBuffer *p, ColorData const c) {
  // adjust the y mouse-parameter to the canvas orientation
  y = p->height() - y;
  // borders for the application
  int window_width = p->width();
  int window_height = p->height();
  // set the start and end positions of the draw mask
  int x_start = x - mask_cols_/2;
  int y_start = y - mask_rows_/2;

  // filter the pixel data from the canvas and the tool through the mask, and
  // apply them to the canvas
  for (int mask_y = 0; mask_y < mask_rows_; mask_y++) {
    for (int mask_x = 0; mask_x < mask_cols_; mask_x++) {
      // set the current pixel to the display buffer that we passed in
      // Check that we do not draw outside the border of the application
      if ((mask_x + x_start) >= 0 && (mask_x + x_start) < window_width &&
        (mask_y + y_start) >= 0 && (mask_y + y_start) < window_height) {
        ColorData pixel = p->get_pixel(x_start + mask_x, y_start + mask_y);
        float mask_filter = static_cast<float>(tool_mask_[mask_y][mask_x]);
        if (uses_luminance_)
          mask_filter *= pixel.luminance();

        // print out the mask; for debugging
        // std::cout << tool_mask_[mask_y][mask_x] << ":";
        ColorData new_pixel = (pixel * (1.0 - mask_filter)) + (c * mask_filter);
        p->set_pixel(mask_x + x_start, mask_y + y_start, new_pixel);
      }
    }
    // skip to next line of mask for printout
    // std::cout << std::endl;
  }
// space between mask printouts
// std::cout << std::endl;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

}  // namespace image_tools
