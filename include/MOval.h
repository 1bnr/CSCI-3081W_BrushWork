//
//  MOval.h
//  Student Support
//
//  Created by Seth Johnson on 2/9/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  MOval is a Mask in the shape of an ellipse with an orientation.
//  It takes an angle in degrees, and a ratio between height and width.
//  It is of constant fill.

#ifndef INCLUDE_MOVAL_H_
#define INCLUDE_MOVAL_H_

#include "Mask.h"

class MOval : public Mask {
 public:
    MOval(float radius, float opacity, float angle, float ratio);
    virtual ~MOval() {}

 protected:
    float getIntensity(int x, int y, float radius);
    float m_angle;
    float m_ratio;
};

#endif  // INCLUDE_MOVAL_H_
