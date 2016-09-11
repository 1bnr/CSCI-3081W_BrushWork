/*******************************************************************************
 * Name            : TEraser.cc
 * Project         : BrushWork
 * Module          : ??
 * Description     : Implementation of eraser tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "TEraser.h"
#include "MConstant.h"
#include "ColorData.h"

#include <string>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
TEraser::TEraser(void) {
  m_mask = new MConstant(10.0, 1.0);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
// Eraser does not blend colors with the toolColor.  Here we are overriding the
// superclass's colorBlendMath to set the canvasColor to the backgroundColor.
ColorData TEraser::colorBlendMath(float mask,
                                  ColorData toolColor,
                                  ColorData canvasColor,
                                  ColorData backgroundColor) {
  return backgroundColor*mask + canvasColor*(1-mask);
}

}  // namespace csci3081
