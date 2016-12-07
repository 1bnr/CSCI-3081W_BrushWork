/*******************************************************************************
 * Name            : quantize.cc
 * Project         : Flashphoto
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
#include <vector>

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
void Quantize::apply_filter(PixelBuffer* p, int buckets) {
  int x = p->width();
  int y = p->height();
  PixelBuffer filtered_buffer = *p;

  // create bucketlist and bound each bucket (index) with a float value
  std::vector<float> bucket_list;
  if (buckets > 2) {
    for (int z = 0; z < buckets; z++) {
      bucket_list.push_back((z * 1.0) / (buckets - 1));
    }
  } else {  // if bucket size is 2
    bucket_list.push_back(0.5);
    bucket_list.push_back(1.0);
  }

  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      ColorData curr_color = p->get_pixel(i, j);
      float curr_color_red = curr_color.red();
      float curr_color_blue = curr_color.blue();
      float curr_color_green =  curr_color.green();
      float new_red;
      float new_green;
      float new_blue;
      // setting red channel
      for (int a = 0; a < buckets; a++) {
        if (curr_color_red < bucket_list[a]) {
          new_red = bucket_list[a];
          break;
        }
      }
      // setting green channel
      for (int b = 0; b < buckets; b++) {
        if (curr_color_green < bucket_list[b]) {
          new_green = bucket_list[b];
          break;
        }
      }
      // setting blue channel
      for (int c = 0; c < buckets; c++) {
        if (curr_color_blue < bucket_list[c]) {
          new_blue = bucket_list[c];
          break;
        }
      }
      ColorData clamped = ColorData(new_red, new_green, new_blue);
      clamped = clamped.clamped_color();
      filtered_buffer.set_pixel(i, j, clamped);  // set new pixel
    }
  }
  *p = filtered_buffer;
}
}  // namespace image_tools