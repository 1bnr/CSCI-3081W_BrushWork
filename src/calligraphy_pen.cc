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
  int rows = 15;
  int cols = 5;
  std::vector<std::vector<float>> mask;
  set_mask_rows(rows);
  set_mask_cols(cols);

  // Set up the mask
  mask.resize(rows);
  for (int i = 0; i < rows; ++i) 
    {
    mask[i].resize(cols);
    for (int j = 0; j < cols; j++)
      mask[i][j] = 1;
  }
  set_tool_mask(mask);
}


CalligraphyPen::~CalligraphyPen() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/


}  // namespace image_tools
