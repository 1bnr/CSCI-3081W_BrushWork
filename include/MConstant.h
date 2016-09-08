//
//  MConstant.h
//  Student Support
//
//  Created by Seth Johnson on 2/9/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  MConstant is a Mask that is round, with a constant fill
//  value.


#ifndef INCLUDE_MCONSTANT_H_
#define INCLUDE_MCONSTANT_H_

#include "Mask.h"

class MConstant : public Mask {
 public:
        MConstant(float radius, float opacity);

 protected:
        float getIntensity(int x, int y, float radius);
};

#endif  // INCLUDE_MCONSTANT_H_
