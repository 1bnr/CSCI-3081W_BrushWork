/*******************************************************************************
 * Name            : t_highlighter.cc
 * Project         : BrushWork
 * Module          : Tool
 * Description     : Implementation of highlighter tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/t_highlighter.h"
#include <string>
#include "include/m_oval.h"
#include "include/color_data.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
THighlighter::THighlighter(void) {
    mask(new MOval(7.0, 0.4, 90, 0.3));
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
// Overrides the super's function to include the luminance of the canvasColor
// in the calculation of the tool's intensity
    ColorData THighlighter::color_blend_math(float mask,
                                       ColorData toolColor,
                                       ColorData canvasColor,
                                       ColorData backgroundColor) {
  float L = canvasColor.luminance();
  float intensity = mask*L;
  return toolColor*intensity + canvasColor*(1.0-intensity);
}

}  // namespace image_tools
