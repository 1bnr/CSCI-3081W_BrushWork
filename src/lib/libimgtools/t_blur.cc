/*******************************************************************************
 * Name            : t_blur.cc
 * Project         : FlashPhoto
 * Module          : Tool
 * Description     : Implementation of blur tool class
 * Copyright       : 2016 Abner Holsinger. All rights reserved.
 * Creation Date   : 11/20/16
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/t_blur.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include "include/color_data.h"
#define MASK_SIZE 35

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
TBlur::TBlur(void) : w_width_(0), w_height_(0) {
  mask(new MLinear(MASK_SIZE/2, 0.2));
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
/* blur tool application method, uses linear fall-off mask to vary the amount
 * of blur to blend with each pixel within the mask
 */
void TBlur::ApplyToBuffer(int x, int y, ColorData tool_color,
    PixelBuffer* buffer,
    PixelBuffer* stamp) {

  // borders for the application
  w_width_ = buffer->width();
  w_height_ = buffer->height();

  // set the start and end positions of the draw mask
  int x_start = x - MASK_SIZE/2;
  int y_start = y - MASK_SIZE/2;
  Mask * l_mask;
  l_mask = mask();
  const float * mask_array = l_mask->float_array();
  // filter the pixel data from the canvas and the tool through the mask, and
  // apply them to the canvas
  for (int mask_y = 0; mask_y < MASK_SIZE; mask_y++) {
    int y_offset = y_start + mask_y;
    if (!is_in_bounds(x, y_offset)) {
      x++;
      continue;
    }
    for (int mask_x = 0; mask_x < MASK_SIZE; mask_x++) {
      ColorData new_pixel, pixel;
      /* Check that we do not draw outside the border of the application */
      int x_offset = x_start + mask_x;
      if (!is_in_bounds(x_offset, y_offset))
        continue;
      pixel = buffer->get_pixel(x_offset, y_offset);
      float mask_filter = mask_array[(MASK_SIZE*mask_y) + mask_x];
      /* use a kernel radius 3; total kernel width 7 */
      int kernel_r = 2;
      /* get the new pixel from the  blur kernel */
      new_pixel = blur_kernel(x_offset, y_offset, kernel_r, *buffer);

      /* mix new_pixel with canvas pixel through the linear fall-off mask */
      new_pixel = (pixel * (1.0 - mask_filter)) + (new_pixel * mask_filter);
      if (is_in_bounds(x_offset, y_offset))
        buffer->set_pixel(x_offset, y_offset, new_pixel.clamped_color());
    }
  }
}
/* this is the kernel; get the pixels within radius of x_center, y_center */
ColorData TBlur::blur_kernel(int x_center, int y_center, int radius,
                                         const PixelBuffer &buffer) {
  int start_x = x_center - radius;
  int end_x = x_center + radius;
  int start_y = y_center - radius;
  int end_y = y_center + radius;
  ColorData pixel = buffer.get_pixel(x_center, y_center);
  std::vector<ColorData> samples;
  for (int y = start_y; y < end_y; y++) {
    if (!is_in_bounds(x_center, y))
      continue;
    for (int x = start_x; x < end_x; x++) {
      /* skip any pixel coords that fall outside canvas */
      if (!is_in_bounds(x, y))
        continue;
      /* collect all the pixels that fall within kernel radius */
      if (sqrt(((x - x_center) * (x - x_center)) +
               ((y - y_center) * (y - y_center))) < radius)
        samples.push_back(buffer.get_pixel(x, y));
    }
  }
  int sample_count = samples.size();
  float sample_div = 1.0/(sample_count + 1);
  ColorData new_pixel = pixel * sample_div;
  /* if we have samples to blend */
  if (sample_count > 0) {
    /* iterate through the sample pixels */
    std::vector <ColorData>::iterator cd;
    for (cd = samples.begin(); cd != samples.end(); cd++)
      new_pixel = (*cd * sample_div)  + new_pixel; /* and mix them */
  }
  return new_pixel;
}

/* check that a given point x,y is within the bounds the canvas */
bool TBlur::is_in_bounds(int x, int y) {
  return (x > 0 && x < w_width_ && y > 0 && y < w_height_);
}
}  /* namespace image_tools */
