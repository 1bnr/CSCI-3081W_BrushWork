/*******************************************************************************
 * Name            : calligraphy_pen.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Calligraphy Pen class
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 10/06/16
 * Original Author : Ben Bramanti
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/calligraphy_pen.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
CalligraphyPen::CalligraphyPen() : Tool() {
  mask_rows_ = 15;
  mask_cols_ = 5;

  // Set up the tool_mask_
  tool_mask_.resize(mask_rows_);
  for (int i = 0; i < mask_rows_; ++i) 
    {
    tool_mask_[i].resize(mask_cols_);
    for (int j = 0; j < mask_cols_; j++)
      tool_mask_[i][j] = 1;
    }
}


CalligraphyPen::~CalligraphyPen() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/


}  // namespace image_tools
