/*******************************************************************************
 * Name            : saturate.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Threshold class
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/14/16
 * Original Author : Isaac Schwab
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/saturate.h"
#include <cmath> 

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Saturate::Saturate() {}

Saturate::~Saturate() {}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 void Saturate::apply_filter(PixelBuffer* p, float saturate_amount){
   int x = p->width();
   int y = p->height();
   float gray_scale;
   PixelBuffer filtered_buffer = *p;
   for(int i = 0; i<x; i++){
     for (int j = 0; j<y; j++){
       // Get the grayscale value for each pixel using the luminance function
       gray_scale = p->get_pixel(i,j).luminance();
       // Get the actual color of the pixel and the grayscale color
       // And interpolate between them using the satuarate_amount
       ColorData gray = ColorData(gray_scale, gray_scale, gray_scale);
       ColorData color = p->get_pixel(i,j);
       ColorData new_color = (color * saturate_amount) + (gray * (1 - saturate_amount));
       new_color = new_color.clamped_color();
       filtered_buffer.set_pixel(i,j, new_color);
     }
   }
   *p = filtered_buffer;
 }
}  // namespace image_tools
