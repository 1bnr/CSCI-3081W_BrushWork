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
  int rows = 41;
  int cols = 41;
  std::vector<std::vector<float>> mask;
  set_mask_rows(rows);
  set_mask_cols(cols);
  // find center of mask for linear falloff
  int center = cols / 2;
  double slope = -0.2/static_cast<double>(center);

  // Set up the mask
  mask.resize(rows);
  for (int x = 0; x < rows; x++) {
    mask[x].resize(cols);
    for (int y = 0; y < cols; y++) {
      // if inside circle, calculate mask filter values
      if ((pow(x - center, 2) + pow(y - center, 2)) <= pow(center, 2))
        mask[x][y] = ((sqrt(pow(x - center, 2) + pow(y - center, 2))
                            - center) * slope);
      else  // outside circle, set filter value to 0
        mask[x][y] = 0;
    }
  }
  set_tool_mask(mask);
}
SprayCan::~SprayCan() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
}  // namespace image_tools
