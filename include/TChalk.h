/*******************************************************************************
 * Name            : TChalk.h
 * Project         : csci3081
 * Module          : Tool
 * Description     : Header file for Chalk class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_TCHALK_H_
#define INCLUDE_TCHALK_H_

/*******************************************************************************
 * Includes
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
 * @brief This tool simulates the usage of Chalk.
 * It has an MLinear mask with a radius of 5.0 (diameter of 11), an opacity of
 * 1.0 (completely opaque).  color_blend_math is overriden to randomly change
 * the tool's intensity at a pixel.
 */
class TChalk : public Tool {
 public:
  TChalk(void);

  ColorData color_blend_math(
      float mask_pixel_amount,
      ColorData tool_color,
      ColorData current_color,
      ColorData background_color);

  std::string name(void) { return "Chalk"; }

 private:
  unsigned seed_; /** Random seed for use with color blending */
};
}  // namespace csci3081

#endif  // INCLUDE_TCHALK_H_
