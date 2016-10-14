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
  int rows = 3;
  int cols = 3;
  std::vector<std::vector<float>> mask;
  set_mask_rows(rows);
  set_mask_cols(cols);

  // Set up the mask
  mask.resize(rows);
  for (int i = 0; i < rows; ++i)
    mask[i].resize(cols);

  int center = cols / 2;
  for (int y = 0; y < rows; y++) {
    mask[y].resize(cols);
    for (int x = 0; x < cols; x++) {
      int xy_pos = pow(x - center, 2) + pow(y - center, 2);
      // if inside circle, set filter to 1; apply color opaque
      if ( xy_pos <= pow(center, 2) )
        mask[x][y] = 1;
      else  // outside circle, set filter value to 0; block color application
        mask[x][y] = 0;
      }
    }
    set_tool_mask(mask);
}
Pen::~Pen() {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

}  // namespace image_tools
