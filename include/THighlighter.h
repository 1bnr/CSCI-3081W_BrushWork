/*******************************************************************************
 * Name            : THighlighter.h
 * Project         : csci3081
 * Module          : Tool
 * Description     : Header file for Highlighter class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_THIGHLIGHTER_H_
#define INCLUDE_THIGHLIGHTER_H_

/*******************************************************************************
 * Include Definitions
 ******************************************************************************/
#include "Tool.h"
#include <string>

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This tool simulates the usage of a Highlighter.
 * It has a MOval mask with a radius of 7.0 (diameter of 15), an opacity of 0.4
 * (semi-transparent), an angle of 90 degrees counter-clockwise from the x-axis,
 * and an elongation ratio of 0.3
 */
class THighlighter : public Tool {
 public:
  THighlighter(void);

  // overrides super's implementation
  ColorData color_blend_math(
      float mask_pixel_amount,
      ColorData tool_color,
      ColorData current_color,
      ColorData background_color);

  std::string name(void) { return "Highlighter"; }
};
}  // namespace csci3081

#endif  // INCLUDE_THIGHLIGHTER_H_
