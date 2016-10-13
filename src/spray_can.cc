/*******************************************************************************
 * Name            : spray_can.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Pen class
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 10/09/16
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/spray_can.h"
#include <iostream>
#include <cmath>
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
SprayCan::SprayCan() {
  // generate mask; values are to be between 0.0 and 1.0
  mask_rows_ = 41;
  mask_cols_ = 41;
  // find center of mask for linear falloff
  int center_ = mask_cols_ / 2;
  double slope = -0.2/static_cast<double>(center_);

  // Set up the tool_mask_
  tool_mask_.resize(mask_rows_);
  for (int x = 0; x < mask_rows_; x++) {
    tool_mask_[x].resize(mask_cols_);
    for (int y = 0; y < mask_cols_; y++) {
      // if inside circle, calculate mask filter values
      if ((pow(x - center_, 2) + pow(y - center_, 2)) <= pow(center_, 2))
        tool_mask_[x][y] = ((sqrt(pow(x - center_, 2) + pow(y - center_, 2))
                            - center_) * slope);
      else  // outside circle, set filter value to 0
        tool_mask_[x][y] = 0;
    }
  }
}
SprayCan::~SprayCan() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
}  // namespace image_tools
