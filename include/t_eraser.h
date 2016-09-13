/*******************************************************************************
 * Name            : t_eraser.h
 * Project         : csci3081
 * Module          : Tool
 * Description     : Header file for Eraserclass
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_T_ERASER_H_
#define INCLUDE_T_ERASER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "include/tool.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This tool simulates the usage of an Eraser.
 * It has a constant mask with a radius of 10.0 (diameter of 21) and an
 * opacity of 1.0 Eraser overrides the color_blend_math() function to provide its
 * special eraser functionality.
 */
class TEraser : public Tool {
 public:
  TEraser(void);

  ColorData color_blend_math(
      float mask,
      ColorData toolColor,
      ColorData canvasColor,
      ColorData backgroundColor);

  std::string name(void) { return "Eraser"; }
};
}  // namespace image_tools

#endif  // INCLUDE_T_ERASER_H_
