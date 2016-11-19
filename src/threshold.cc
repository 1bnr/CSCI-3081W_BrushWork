/*******************************************************************************
 * Name            : threshold.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Threshold class
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/12/16
 * Original Author : Ben Bramanti
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/threshold.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Threshold::Threshold() {}

Threshold::~Threshold() {}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 void Threshold::apply_filter(PixelBuffer* p, float thresh_amount){
   int x = p->width();
   int y = p->height();
   PixelBuffer filtered_buffer = *p;
   float new_red;
   float new_green;
   float new_blue;

   for(int i = 0; i<x; i++){
     for (int j = 0; j<y; j++){
       if (p->get_pixel(i,j).red() > thresh_amount){
         new_red = 1.0;
         }
       else{
         new_red = 0.0;
       }
       if (p->get_pixel(i,j).green() > thresh_amount){
         new_green = 1.0;
       }
       else{
         new_green = 0.0;
       }
       if (p->get_pixel(i,j).blue() > thresh_amount){
         new_blue = 1.0;
       }
       else{
         new_blue = 0.0;
       }
       ColorData clamped = ColorData(new_red,new_green,new_blue);
       clamped = clamped.clamped_color();
       filtered_buffer.set_pixel(i,j,clamped);
     }
   }
   *p = filtered_buffer;
 }
}  // namespace image_tools
