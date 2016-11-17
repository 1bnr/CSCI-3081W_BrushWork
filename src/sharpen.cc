/*******************************************************************************
 * Name            : sharpen.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Sharpen class
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/17/16
 * Original Author : Isaac Schwab
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/sharpen.h"
#include <cmath>
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Sharpen::Sharpen() {}

Sharpen::~Sharpen() {}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 void Sharpen::apply_filter(PixelBuffer* p, float sharpen_amount){
   int x = p->width();
   int y = p->height();
   PixelBuffer filtered_buffer = PixelBuffer(*p);
   int mask_rows_ = 3;
   int mask_cols_ = 3;
   std::vector<std::vector<float>> kernel = {{0.0, -1.0, 0.0},
                                             {-1.0, 5.0, -1.0},
                                             {0.0, -1.0, 0.0}};

   // Main loop through all the pixels in the Pixel Buffer
   for(int i = 0; i<x; i++){
     for (int j = 0; j<y; j++){
       // Get kernel values, and color from current pixel
       ColorData og_color = ColorData(0,0,0);
       int window_width = p->width();
       int window_height = p->height();
       // set the start and end positions of the draw mask
       int x_start = i - mask_cols_/2;
       int y_start = j - mask_rows_/2;
       // Now actually loop through and apply the kernel to each pixel
       for (int mask_y = 0; mask_y < mask_rows_; mask_y++) {
        for (int mask_x = 0; mask_x < mask_cols_; mask_x++) {
          // set the current pixel to the display buffer that we passed in
          // Check that we do not draw outside the border of the application
          if ((mask_x + x_start) >= 0 && (mask_x + x_start) < window_width &&
            (mask_y + y_start) >= 0 && (mask_y + y_start) < window_height) {
            std::cout << i << ", " << j << std::endl;
            ColorData temp = p->get_pixel(x_start + mask_x, y_start + mask_y);
            // Compute the new color pixel
            //std::cout << "Kernel val" << kernel[mask_x][mask_y] << std::endl;
            temp = temp * kernel[mask_x][mask_y];
            og_color = og_color + temp;
          }
        }
       }
     filtered_buffer.set_pixel(i,j, og_color);
   }
   *p = filtered_buffer;
 }
}  // namespace image_tools
}