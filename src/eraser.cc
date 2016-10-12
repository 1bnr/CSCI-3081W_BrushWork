/*******************************************************************************
 * Name            : eraser.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Eraser class
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 10/05/16
 * Original Author : Ben Bramanti
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include "include/eraser.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
 Eraser::Eraser() : Tool() {
   mask_rows_ = 21;
   mask_cols_ = 21;

   // Set up the tool_mask_
   tool_mask_.resize(mask_rows_);
   for (int i = 0; i < mask_rows_; ++i)
     tool_mask_[i].resize(mask_cols_);

   //Initialize the mask
  // Set up the tool_mask_
  int center_ = mask_cols_ / 2;
  tool_mask_.resize(mask_rows_);
  for (int x = 0; x < mask_rows_; ++x) {
    tool_mask_[x].resize(mask_cols_);
    for (int y = 0; y < mask_cols_; y++) {
      int xy_pos = pow(x - center_, 2) + pow(y - center_, 2);
      // if inside circle, calculate mask filter values
      if ( xy_pos < pow(center_, 2) )
        tool_mask_[x][y] = 1;
      else  // outside circle, set filter value to 0
        tool_mask_[x][y] = 0;
    }
  }
}

 Eraser::~Eraser() {
 }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/


}  // namespace image_tools
