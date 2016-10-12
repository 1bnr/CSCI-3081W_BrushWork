/*******************************************************************************
 * Name            : pen.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Pen class
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 10/06/16
 * Original Author : Ben Bramanti
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include "include/pen.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Pen::Pen() : Tool() {
  mask_rows_ = 3;
  mask_cols_ = 3;

   // Set up the tool_mask_
   tool_mask_.resize(mask_rows_);
   for (int i = 0; i < mask_rows_; ++i)
     tool_mask_[i].resize(mask_cols_);

  int center_ = mask_cols_ / 2;
  for (int y = 0; y < mask_rows_; y++) {
    tool_mask_[y].resize(mask_cols_);
    for (int x = 0; x < mask_cols_; x++) {
      int xy_pos = pow(x - center_, 2) + pow(y - center_, 2);
      // if inside circle, set filter to 1; apply color opaque
      if ( xy_pos <= pow(center_, 2) )
        tool_mask_[x][y] = 1;
      else  // outside circle, set filter value to 0; block color application
        tool_mask_[x][y] = 0;
      }
   }
}
Pen::~Pen() {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

}  // namespace image_tools
