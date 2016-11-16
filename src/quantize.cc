/*******************************************************************************
 * Name            : quantize.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Quantize class
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 11/15/16
 * Original Author : Ben Bramanti
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/quantize.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Quantize::Quantize() {}

Quantize::~Quantize() {}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 void Quantize::apply_filter(PixelBuffer* p, int buckets){
   int x = p->width();
   int y = p->height();
   PixelBuffer filtered_buffer = *p;

   float bucket_list[buckets];
   for (int x = 0; x < buckets; x++){
     bucket_list[x] = (x * 1.0) / (buckets-1);
   }

   for(int i = 0; i<x; i++){
     for (int j = 0; j<y; j++){
       ColorData curr_color = p->get_pixel(i,j);
    	 float curr_color_red = curr_color.red();
    	 float curr_color_blue = curr_color.blue();
    	 float curr_color_green =  curr_color.green();
       float new_red;
       float new_green;
       float new_blue;

      // setting red channel
       for (int x = 0; x < buckets; x++){
         if (curr_color_red < bucket_list[x]){
           new_red = bucket_list[x];
           break;
         }
       }

       // setting green channel
        for (int x = 0; x < buckets; x++){
          if (curr_color_green < bucket_list[x]){
            new_green = bucket_list[x];
            break;
          }
        }

        // setting blue channel
         for (int x = 0; x < buckets; x++){
           if (curr_color_blue < bucket_list[x]){
             new_blue = bucket_list[x];
             break;
           }
         }
      filtered_buffer.set_pixel(i, j, ColorData(new_red, new_green, new_blue));
     }
   }
   *p = filtered_buffer;
 }
}  // namespace image_tools
