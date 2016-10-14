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
  int rows = 21;
  int cols = 21;
  std::vector<std::vector<float>> mask;
  set_mask_rows(rows);
  set_mask_cols(cols);

  // Set up the mask
  mask.resize(rows);
  for (int i = 0; i < rows; ++i)
    mask[i].resize(cols);

  //Initialize the mask
  // Set up the mask
  int center = cols / 2;
  mask.resize(rows);
  for (int x = 0; x < rows; ++x) {
    mask[x].resize(cols);
    for (int y = 0; y < cols; y++) {
      int xy_pos = pow(x - center, 2) + pow(y - center, 2);
      // if inside circle, calculate mask filter values
      if ( xy_pos < pow(center, 2) )
        mask[x][y] = 1;
      else  // outside circle, set filter value to 0
        mask[x][y] = 0;
    }
  }
  set_tool_mask(mask);
}

Eraser::~Eraser() {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/


}  // namespace image_tools
