/*******************************************************************************
 * Name            : t_eraser.cc
 * Project         : BrushWork
 * Module          : Tool
 * Description     : Implementation of eraser tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/t_eraser.h"
#include <string>
#include "include/m_constant.h"
#include "include/color_data.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
TEraser::TEraser(void) { mask(new MConstant(10.0, 1.0)); }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
// Eraser does not blend colors with the toolColor.  Here we are overriding the
// superclass's color_blend_math to set the canvasColor to the backgroundColor.
ColorData TEraser::color_blend_math(float mask,
                                  ColorData toolColor,
                                  ColorData canvasColor,
                                  ColorData backgroundColor) {
  return backgroundColor*mask + canvasColor*(1-mask);
}

}  // namespace image_tools
