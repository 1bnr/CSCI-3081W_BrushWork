/*******************************************************************************
 * Name            : MConstant.h
 * Project         : csci3081
 * Module          : ??
 * Description     : Header File for Constant Mask class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_MCONSTANT_H_
#define INCLUDE_MCONSTANT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Mask.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
//  MConstant is a Mask that is round, with a constant fill
//  value.
class MConstant : public Mask {
 public:
        MConstant(float radius, float opacity);

 protected:
        float getIntensity(int x, int y, float radius);
};

}  // namespace csci3081

#endif  // INCLUDE_MCONSTANT_H_
