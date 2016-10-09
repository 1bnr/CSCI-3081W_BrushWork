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

  int center_ = ( mask_rows_ / 2);
  double slope = -0.2/static_cast<double>(center_);

  // Set up the tool_mask_
  tool_mask_.resize(mask_rows_);
  for (int i = 0; i < mask_rows_; ++i)
    {
    tool_mask_[i].resize(mask_cols_);
    for (int j = 0; j < (mask_cols_); j++)
      {
      // if inside circle, calculate mask filter values
      if ((pow(i - center_, 2) + pow(j - center_, 2)) <= pow(center_, 2))
        tool_mask_[i][j] = ((sqrt(pow(i - center_, 2) + pow(j - center_, 2)) - center_) * slope);
      else // set filter value to 0
        tool_mask_[i][j] = 0;
      }
    }
//  tool_mask_ = mask;
}



SprayCan::~SprayCan() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/


}  // namespace image_tools
