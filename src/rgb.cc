/*******************************************************************************
 * Name            : rgb.cc
 * Project         : Flashphoto
 * Module          : image_tools
 * Description     : Implementation of Threshold class
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/14/16
 * Original Author : Ben Bramanti
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/rgb.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
RGB::RGB() {}

RGB::~RGB() {}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 void RGB::apply_filter(PixelBuffer* p, float red, float blue, float green){
   int x = p->width();
   int y = p->height();
   PixelBuffer filtered_buffer = *p;
   float new_red;
   float new_green;
   float new_blue;

   for(int i = 0; i<x; i++){
     for (int j = 0; j<y; j++){
       new_red = red * p->get_pixel(i,j).red();
       new_blue = blue * p->get_pixel(i,j).blue();
       new_green = green * p->get_pixel(i,j).green();
       filtered_buffer.set_pixel(i,j,ColorData(new_red,new_green,new_blue));
     }
   }
   *p = filtered_buffer;
 }
}  // namespace image_tools
