/*******************************************************************************
 * Name            : blur.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Pen class
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 10/13/16
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/blur.h"
#include <iostream>
#include <cmath>
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Blur::Blur() {
  // generate mask; values are to be between 0.0 and 1.0
  mask_rows_ = 41;
  mask_cols_ = 41;
  // find center of mask for linear falloff
  int center_ = mask_cols_ / 2;
  double slope = -0.2/static_cast<double>(center_);

  // Set up the tool_mask_
  tool_mask_.resize(mask_rows_);
  for (int x = 0; x < mask_rows_; x++) {
    tool_mask_[x].resize(mask_cols_);
    for (int y = 0; y < mask_cols_; y++) {
      // if inside circle, calculate mask filter values
      if ((pow(x - center_, 2) + pow(y - center_, 2)) <= pow(center_, 2))
        tool_mask_[x][y] = ((sqrt(pow(x - center_, 2) + pow(y - center_, 2))
                            - center_) * slope);
      else  // outside circle, set filter value to 0
        tool_mask_[x][y] = 0;
    }
  }
}
Blur::~Blur() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
// The Draw fucntion, take in a color object & the pointer to display buffer
void Blur::Draw(int x, int y, PixelBuffer *p, ColorData c) {
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
       ColorData pixel_0 = p->get_pixel(x_start + mask_x, y_start + mask_y); // focal pixel
      // Check that we do not draw outside the border of the application
      if ((mask_x + x_start) > 0 && (mask_x + x_start) < (window_width - 1) &&
        (mask_y + y_start) > 0 && (mask_y + y_start) < (window_height - 1)) {
        // get adjacent pixel data
        ColorData pixel_1 = p->get_pixel(x_start + mask_x + 1, y_start + mask_y + 1); // x+1, y+1
        ColorData pixel_2 = p->get_pixel(x_start + mask_x - 1, y_start + mask_y - 1); // x-1, y-1
        ColorData pixel_3 = p->get_pixel(x_start + mask_x + 1, y_start + mask_y - 1); // x+1, y-1
        ColorData pixel_4 = p->get_pixel(x_start + mask_x - 1, y_start + mask_y + 1); // x-1, y+1

        float mask_filter = static_cast<float>(tool_mask_[mask_y][mask_x]);
  
        // print out the mask; for debugging
        // std::cout << tool_mask_[mask_y][mask_x] << ":";
        ColorData new_pixel = (pixel_0 * (0.6)) + (pixel_1 * (0.1)) + (pixel_2 * (0.1)) + (pixel_3 * (0.1)) + (pixel_4 * (0.1));
        new_pixel = (pixel_0 * (1.0 - mask_filter)) + (new_pixel * mask_filter);
        p->set_pixel(mask_x + x_start, mask_y + y_start, new_pixel);
      }
    }
    // skip to next line of mask for printout
    // std::cout << std::endl;
  }
// space between mask printouts
// std::cout << std::endl;
}
}  // namespace image_tools
