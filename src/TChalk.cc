/*******************************************************************************
 * Name            : TChalk.cc
 * Project         : BrushWork
 * Module          : ??
 * Description     : Implementation of chalk tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "TChalk.h"
#include "MLinear.h"
#include "ColorData.h"
#include <cmath>
#include <cstdlib>
#include <string>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
TChalk::TChalk() : m_rand_seed(0) {
        m_mask = new MLinear(5.0, 1.0);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
std::string TChalk::getName() {
        return "Chalk";
}

//  A random number between 0.0 and 1.0 is multiplied by a brightened_mask to
//      vary the intensity used in the blending math
ColorData TChalk::colorBlendMath(float mask,
                                 ColorData toolColor,
                                 ColorData canvasColor,
                                 ColorData backgroundColor) {
        float r = static_cast <float> (rand_r(&m_rand_seed))/static_cast <float>(RAND_MAX);
        float brightened_mask = (mask/2+0.5);
        float intensity = round(brightened_mask*r);
        return toolColor*intensity + canvasColor*(1.0-intensity);
}

}  // namespace csci3081
