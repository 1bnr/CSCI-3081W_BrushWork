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

  //Initialize the mask
  tool_mask_[0] = {0.0, 1, 0.0};
  tool_mask_[1] = {1, 1, 1};
  tool_mask_[2] = {0.0, 1, 0.0};
}

Pen::~Pen() {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/


}  // namespace image_tools
