/*******************************************************************************
 * Name            : blur.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Threshold class
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/16/16
 * Original Author : Isaac Schwab
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/blur.h"
#include <cmath> 
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Blur::Blur() {}

Blur::~Blur() {}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 void Blur::apply_filter(PixelBuffer* p, float blur_amount){
   int x = p->width();
   int y = p->height();
   int bounds = static_cast<int>(floor(blur_amount));
   if (bounds % 2 == 0) {
    bounds++;
   }
   std::cout << "bounds: " << bounds << std::endl;
   float blur_frac = 1.0 / ((2*bounds)-1);
   PixelBuffer filtered_buffer = PixelBuffer(*p);
   int mask_rows_ = bounds;
   int mask_cols_ = bounds;
   // std::vector<std::vector<float>> kernel = {{0.0, blur_frac, 0.0},
   //                                          {blur_frac, blur_frac, blur_frac},
   //                                          {0.0, blur_frac, 0.0}};
   std::vector<std::vector<float> > kernel(bounds, std::vector<float>(bounds));
   int midpoint = mask_rows_/2;
   std::cout << "midpoint: " << midpoint << std::endl;
   for (int r = 0; r < mask_rows_; r++) {
    for (int c = 0; c < mask_cols_; c++) {
      if (r == midpoint || c == midpoint) {
        kernel[r][c] = blur_frac;
      }
      else {
        kernel[r][c] = 0; 
      }
      std::cout << " , " << kernel[r][c] << " , ";
    }
    std::cout << std::endl;
   }
   std::cout << "x,y: " << x << ", " << y << std::endl;                                       
   for(int i = 0; i<x; i++){
     for (int j = 0; j<y; j++){
       // Get kernel values, and color from current pixel
       ColorData og_color = ColorData(0,0,0);
       int window_width = p->width();
       int window_height = p->height();
       // set the start and end positions of the draw mask
       int x_start = i - mask_cols_/2;
       int y_start = j - mask_rows_/2;
       for (int mask_y = 0; mask_y < mask_rows_; mask_y++) {
        for (int mask_x = 0; mask_x < mask_cols_; mask_x++) {
          // set the current pixel to the display buffer that we passed in
          // Check that we do not draw outside the border of the application
          if ((mask_x + x_start) >= 0 && (mask_x + x_start) < window_width &&
            (mask_y + y_start) >= 0 && (mask_y + y_start) < window_height) {
            ColorData temp = p->get_pixel(x_start + mask_x, y_start + mask_y);
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
