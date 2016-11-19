/*******************************************************************************
 * Name            : motion_blur.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Threshold class
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/17/16
 * Original Author : Isaac Schwab
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/motion_blur.h"
#include <cmath>
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
MotionBlur::MotionBlur() {}

MotionBlur::~MotionBlur() {}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MotionBlur::apply_filter(PixelBuffer* p, float motion_blur_amount,
                              int direction) {
  // Direction 0 = North/South, 1 = East/West, 2 = NorthEast/SouthWest
  // 3 = NorthWest/SouthEast
  // PixelBuffer height and width
  int x = p->width();
  int y = p->height();
  std::cout << direction << std::endl;
  // Calculate an odd numbered bound based off the input
  int bounds = static_cast<int>(floor(motion_blur_amount));
  if (bounds % 2 == 0) {
    bounds++;
  }
  std::cout << bounds << std::endl;
  // Kernel variable declarations
  float blur_frac;
  PixelBuffer filtered_buffer = PixelBuffer(*p);
  int mask_rows_ = bounds;
  int mask_cols_ = bounds;
  std::vector<std::vector<float> > kernel(bounds, std::vector<float>(bounds));
  int midpoint = bounds/2;
  for (int r = 0; r < mask_rows_; r++) {
    for (int c = 0; c < mask_cols_; c++) {
      if ((r == midpoint && direction == 0) ||
          (c == midpoint && direction == 1) ||
          (c == r && direction == 2) || (c+r == bounds-1 && direction == 3)) {
        kernel[r][c] = 1.0;
      } else {
        kernel[r][c] = 0.0;
      }
      std::cout << " , " << kernel[r][c] << " , ";
    }
    std::cout << std::endl;
  }

  // Main loop through all the pixels in the Pixel Buffer
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      // Get kernel values, and color from current pixel
      ColorData og_color = ColorData(0, 0, 0);
      int window_width = p->width();
      int window_height = p->height();
      // set the start and end positions of the draw mask
      int x_start = i - mask_cols_/2;
      int y_start = j - mask_rows_/2;
      int blur_count = 0;
      // Build the kernel for each pixel in the PixelBuffer
      for (int mask_y = 0; mask_y < mask_rows_; mask_y++) {
        for (int mask_x = 0; mask_x < mask_cols_; mask_x++) {
          // check if it is in the bounds of the PixelBuffer. If it is in the
          // bounds set the kernel value to 1 and increment the blur_count
          if ((mask_x + x_start) >= 0 && (mask_x + x_start) < window_width &&
            (mask_y + y_start) >= 0 && (mask_y + y_start) < window_height &&
            kernel[mask_x][mask_y] == 1.0) {
            blur_count++;
          }
        }
      }
      // Now actually loop through and apply the kernel to each pixel
      blur_frac = 1.0/blur_count;  // Amount for the kernel
      // reset the loop variables
      x_start = i - mask_cols_/2;
      y_start = j - mask_rows_/2;
      // Loop through and actually apply the blur_frac
      for (int mask_y = 0; mask_y < mask_rows_; mask_y++) {
        for (int mask_x = 0; mask_x < mask_cols_; mask_x++) {
          // set the current pixel to the display buffer that we passed in
          // Check that we do not draw outside the border of the application
          if ((mask_x + x_start) >= 0 && (mask_x + x_start) < window_width &&
            (mask_y + y_start) >= 0 && (mask_y + y_start) < window_height) {
            ColorData temp = p->get_pixel(x_start + mask_x, y_start + mask_y);
            // Compute the new color pixel
            temp = temp * (kernel[mask_x][mask_y] * blur_frac);
            og_color = og_color + temp;
          }
        }
      }
      og_color = og_color.clamped_color();
      filtered_buffer.set_pixel(i, j, og_color);
    }
  }
  *p = filtered_buffer;
}  // end of apply_filter
}  // namespace image_tools
