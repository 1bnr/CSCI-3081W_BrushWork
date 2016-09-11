/*******************************************************************************
 * Name            : MOval.h
 * Project         : csci3081
 * Module          : ??
 * Description     : Header File for Oval mask class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_MOVAL_H_
#define INCLUDE_MOVAL_H_


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
//  MOval is a Mask in the shape of an ellipse with an orientation.
//  It takes an angle in degrees, and a ratio between height and width.
//  It is of constant fill.
class MOval : public Mask {
 public:
    MOval(float radius, float opacity, float angle, float ratio);
    virtual ~MOval() {}

 protected:
    float getIntensity(int x, int y, float radius);
    float m_angle;
    float m_ratio;
};

}  // namespace csci3081

#endif  // INCLUDE_MOVAL_H_
