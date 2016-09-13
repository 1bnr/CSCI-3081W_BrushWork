/*******************************************************************************
 * Name            : t_chalk.cc
 * Project         : BrushWork
 * Module          : Tool
 * Description     : Implementation of chalk tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "t_chalk.h"
#include "m_linear.h"
#include "color_data.h"
#include <cmath>
#include <cstdlib>
#include <string>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
TChalk::TChalk(void) : seed_(0) { mask(new MLinear(5.0, 1.0)); }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
//  A random number between 0.0 and 1.0 is multiplied by a brightened_mask to
// vary the intensity used in the blending math
ColorData TChalk::color_blend_math(float mask,
                                       ColorData toolColor,
                                       ColorData canvasColor,
                                       ColorData backgroundColor) {
  float r = static_cast<float>(rand_r(&seed_))/static_cast <float>(RAND_MAX);
  float brightened_mask = (mask/2+0.5);
  float intensity = round(brightened_mask*r);
  return toolColor*intensity + canvasColor*(1.0-intensity);
}

}  // namespace image_tools
