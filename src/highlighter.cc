/*******************************************************************************
 * Name            : highlighter.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Calligraphy Pen class
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 10/09/16
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/highlighter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Highlighter::Highlighter() : Tool() {
  int rows = 15;
  int cols = 5;
  std::vector<std::vector<float>> mask;
  set_mask_rows(rows);
  set_mask_cols(cols);
  use_luminance();

  // Set up the mask
  mask.resize(rows);
  for (int i = 0; i < rows; ++i) {
    mask[i].resize(cols);
    for (int j = 0; j < cols; j++)
      mask[i][j] = 0.4;
  }
  set_tool_mask(mask);
}
Highlighter::~Highlighter() {}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
}  // namespace image_tools
