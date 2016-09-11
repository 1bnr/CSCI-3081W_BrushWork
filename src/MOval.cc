/*******************************************************************************
 * Name            : MOval.cc
 * Project         : csci3081
 * Module          : ??
 * Description     : Implementation of Oval mask class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "MOval.h"
#include <cmath>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MOval::MOval(float radius, float opacity, float angle, float ratio)
    : Mask(radius, opacity), m_angle(angle), m_ratio(ratio) {
  generateMask();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
float MOval::getIntensity(int x, int y, float radius) {
  float a = radius;
  float b = m_ratio*radius;
  float theta = m_angle/180*M_PI;

  float h = powf(x*cos(theta)+y*sin(theta), 2)/powf(a, 2) +
            powf(x*sin(theta) - y*cos(theta), 2)/powf(b, 2);
  if (h < 1)
    return 1.0;
  else
    return 0.0;
}

}  // namespace csci3081
