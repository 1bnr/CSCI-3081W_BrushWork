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
   float cur_red;
   float cur_green;
   float cur_blue;
   float new_red;
   float new_blue;
   float new_green;
   float gray_scale;
   PixelBuffer filtered_buffer = *p;
   for(int i = 0; i<x; i++){
     for (int j = 0; j<y; j++){
       gray_scale = p->get_pixel(i,j).luminance();
       cur_red = p->get_pixel(i,j).red();
       cur_green = p->get_pixel(i,j).green();
       cur_blue = p->get_pixel(i,j).blue();
       new_red = gray_scale + (saturate_amount*(cur_red-gray_scale));
       new_blue = gray_scale + (saturate_amount*(cur_green-gray_scale));
       new_green = gray_scale + (saturate_amount*(cur_blue-gray_scale));
       filtered_buffer.set_pixel(i,j,ColorData(new_red, new_green, new_blue));
     }
   }
   *p = filtered_buffer;
 }
}  // namespace image_tools
