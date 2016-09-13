/*******************************************************************************
 * Name            : THighlighter.cc
 * Project         : BrushWork
 * Module          : ??
 * Description     : Implementation of highlighter tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Tool_Highlighter.h"
#include "Mask_Oval.h"
#include "ColorData.h"

#include <string>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace csci3081 {

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

}  // namespace csci3081
