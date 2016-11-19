/*******************************************************************************
 * Name            : special.cc
 * Project         : Flashphoto
 * Module          : image_tools
 * Description     : Implementation of Special class
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/18/16
 * Original Author : Ben Bramanti
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/special.h"
#include <cmath>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Special::Special() {}

Special::~Special() {}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Special::apply_filter(PixelBuffer* p) {
  // PixelBuffer height and width
  int x = p->width();
  int y = p->height();
  PixelBuffer filtered_buffer = PixelBuffer(*p);
  // Calculate an odd numbered bound based off the input
  int bounds = 3;
  // Kernel required to create the Edge Detect effect
  std::vector<float> kernel = {-1.0, -1.0, 0.0,
                                -1.0, 0.0, 1.0,
                                0.0, 1.0, 1.0};

  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      // Variables for augmenting the kernel to the PixelBuffer
      int xm_end = i + bounds/2;
      int ym_end = j + bounds/2;
      // This section handles edge detection cases for the kernel
      int kernel_pos = 0;
      int kernel_count = 0;
      ColorData og_color = ColorData(0, 0, 0);
      for (int xm_start = i - bounds/2; xm_start <= xm_end; xm_start++) {
        for (int ym_start = j - bounds/2; ym_start <= ym_end; ym_start++) {
          if (xm_start >= 0 && ym_start >= 0 && xm_start < x && ym_start < y) {
            kernel_count++;  // Counter that keeps track of valid kernel pos
          }
        }
      }
      // Create the new value that will add to 1 for the kernel
      float kernel_val = 8.0 / (kernel_count-1);
      // Actually loop through the surrounding pixels and apply the kernel
      for (int xm_start = i-bounds/2; xm_start <= xm_end; xm_start++) {
        for (int ym_start = j-bounds/2; ym_start <= ym_end; ym_start++) {
          if (xm_start >= 0 && ym_start >= 0 && xm_start < x && ym_start < y) {
            ColorData temp = p->get_pixel(xm_start, ym_start);
            // We dont't want to change the middle kernel value
            if (kernel_pos == 4) {
              temp = temp * kernel[kernel_pos];
            } else {  // Set the kernel val and the generate the new color
              temp = temp * kernel[kernel_pos] * kernel_val;
            }
            og_color = og_color + temp;  // Color accumulator for actual pixel
          }
          kernel_pos++;  // Keep track of where we are in the kernel
        }
      }
      float greyscale = og_color.luminance();
      ColorData final_color = ColorData(greyscale, greyscale, greyscale);
      final_color = final_color.clamped_color();
      filtered_buffer.set_pixel(i, j, final_color);  // Set the new pixel
    }
  }
  *p = filtered_buffer;  // Set the input buffer to our working buffer
}
}  // namespace image_tools
