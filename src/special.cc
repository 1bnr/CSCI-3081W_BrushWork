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
 void Special::apply_filter(PixelBuffer* p){
   int x = p->width();
   int y = p->height();
   PixelBuffer filtered_buffer = *p;
   for(int i = 0; i<x; i++){
     for (int j = 0; j<y; j++){
       ColorData pix = p->get_pixel(i,j);
       float pix_red = pix.red();
       float pix_blue = pix.blue();
       float pix_green = pix.green();
       if (pix_red > pix_blue || pix_red > pix_green){
        pix_red = pix_red + (pix_blue * pix_green);
        }
       if (pix_blue > pix_red || pix_blue > pix_green){
        pix_blue = pix_blue + (pix_red * pix_green);
        }
       if (pix_green > pix_blue || pix_green > pix_red){
        pix_green = pix_green + (pix_red * pix_blue);
        }
       ColorData new_color = ColorData(pix_red,pix_green,pix_blue);
       filtered_buffer.set_pixel(i,j,new_color);
     }
   }
   *p = filtered_buffer;
 }
}  // namespace image_tools
