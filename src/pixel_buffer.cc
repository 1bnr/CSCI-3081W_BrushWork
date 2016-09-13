/*******************************************************************************
 * Name            : pixel_buffer.cc
 * Project         : BrushWork
 * Module          : ??
 * Description     : Implementation of PixelBuffer class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "PixelBuffer.h"
#include "ColorData.h"

#include <iostream>
#include <cstring>

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
using std::cerr;
using std::endl;
namespace csci3081 {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
PixelBuffer::PixelBuffer(int w,
                         int h,
                         ColorData backgroundColor)
    : width_(w),
      height_(h),
      pixels_(w*h,backgroundColor),
      background_color_(new ColorData(backgroundColor)) {}

PixelBuffer::~PixelBuffer(void) {
  delete background_color_;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ColorData PixelBuffer::get_pixel(int x, int y) const {
  ColorData pixelData;

  if ((x < 0) || (x >= width_) || (y < 0) || (y >= height_)) {
    cerr << "getPixel: x,y out of range: " << x << " " << y << endl;
  } else {
    int index = x + width_*(y);
    pixelData = pixels_[index];
  }
  return pixelData;
}

void PixelBuffer::set_pixel(int x, int y, const ColorData& newPixel) {
  if ((x < 0) || (x >= width_) || (y < 0) || (y >= height_)) {
    cerr << "setPixel: x,y out of range: " << x << " " << y << endl;
  } else {
    int index = x + width_*(y);  // x + width*(height-(y+1));
    pixels_[index] = newPixel;
  }
}

/*******************************************************************************
 * Operator Definitions
 ******************************************************************************/
PixelBuffer& PixelBuffer::operator=(
    const PixelBuffer &rhs) {
  /* Check for self-assignment! */
  if (this == &rhs) {
    return *this;
  }
  if (this->width() != rhs.width() ||
      this->height() != rhs.height()) {
    cerr << "CopyPixelBuffer: dimension mismatch" << endl;
  } else {
    this->pixels_ = rhs.pixels_;
  }
  return *this;
} /* operator=() */

}  // namespace csci3081
