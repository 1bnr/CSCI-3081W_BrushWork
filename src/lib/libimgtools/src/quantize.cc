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
#include <cmath>
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
  int steps = buckets - 1;
  // create bucketlist and bound each bucket (index) with a float value
  std::vector<float> bucket_list;
  if (buckets > 2) {
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < y; j++) {
        ColorData c = p->get_pixel(i, j);
        float red = c.red();
        float blue = c.blue();
        float green = c.green();
        red = round(red*steps)/steps;
        green = round(green*steps)/steps;
        blue = round(blue*steps)/steps;
        ColorData output(red, green, blue);
        filtered_buffer.set_pixel(i, j, output);  // set new pixel
      }
    }
    *p = filtered_buffer;
  }
}
}  // namespace image_tools
