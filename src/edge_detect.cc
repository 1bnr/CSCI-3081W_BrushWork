/*******************************************************************************
 * Name            : edge_detect.cc
 * Project         : Flashphoto
 * Module          : image_tools
 * Description     : Implementation of Edge Detect class
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/16/16
 * Original Author : Ben Bramanti
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/edge_detect.h"
#include <cmath>
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
EdgeDetect::EdgeDetect() {}

EdgeDetect::~EdgeDetect() {}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 void EdgeDetect::apply_filter(PixelBuffer* p){
   int x = p->width();
   int y = p->height();
   PixelBuffer filtered_buffer = PixelBuffer(*p);
   int mask_rows_ = 3;
   int mask_cols_ = 3;
   std::vector<std::vector<float>> kernel = {{-1.0, -1.0, -1.0},
                                             {-1.0, 8.0, -1.0},
                                             {-1.0, -1.0, -1.0}};

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
          if ((mask_x + x_start) >= 0 && (mask_x + x_start) < window_width &&
            (mask_y + y_start) >= 0 && (mask_y + y_start) < window_height) {
          //  std::cout << "x: " << x_start+mask_x << " y: " << y_start+mask_y << std::endl;
            ColorData temp = p->get_pixel(i + mask_x, j + mask_y);
            // Compute the new color pixel
            temp = temp * kernel[mask_x][mask_y];
            og_color = og_color + temp;
          }
        }
     }
     filtered_buffer.set_pixel(i,j,og_color);
   }
   *p = filtered_buffer;
 }
 }
}  // namespace image_tools