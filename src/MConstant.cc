/*******************************************************************************
 * Name            : MConstant.cc
 * Project         : csci3081
 * Module          : ??
 * Description     : Implementation of Constant mask class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "MConstant.h"
#include <cmath>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MConstant::MConstant(float radius, float opacity) : Mask(radius, opacity) {
        generateMask();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
float MConstant::getIntensity(int x, int y, float radius) {
        float hyp = sqrt(x*x + y*y);
        if (hyp > radius) {
                return 0.0;
        } else {
                return 1.0;
        }
}
}  // namespace csci3081
