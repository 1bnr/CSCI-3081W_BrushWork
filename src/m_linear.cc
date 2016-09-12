/*******************************************************************************
 * Name            : MLinear.cc
 * Project         : csci3081
 * Module          : ??
 * Description     : Implementation of Linear mask class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "MLinear.h"
#include <cmath>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MLinear::MLinear(float radius, float opacity) : Mask(radius, opacity) {
  generateMask();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
float MLinear::get_intensity(int x, int y, float radius) {
  float hyp = sqrt(x*x + y*y);

  if (hyp <= radius) {
    return 1 - hyp/radius;
  } else {
    return 0.0;
  }
}

}  // namespace csci3081
