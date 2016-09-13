/*******************************************************************************
 * Name            : t_highlighter.h
 * Project         : image_tools
 * Module          : Tool
 * Description     : Header file for Highlighter class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_T_HIGHLIGHTER_H_
#define INCLUDE_T_HIGHLIGHTER_H_

/*******************************************************************************
 * Include Definitions
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
 * @brief This tool simulates the usage of a Highlighter.
 * It has a oval mask with a radius of 7.0 (diameter of 15), an opacity of 0.4
 * (semi-transparent), an angle of 90 degrees counter-clockwise from the x-axis,
 * and an elongation ratio of 0.3
 */
class THighlighter : public Tool {
 public:
  THighlighter(void);

  // overrides super's implementation
  ColorData color_blend_math(
      float mask,
      ColorData toolColor,
      ColorData canvasColor,
      ColorData backgroundColor);

  std::string name(void) { return "Highlighter"; }
};
}  // namespace image_tools

#endif  // INCLUDE_T_HIGHLIGHTER_H_
