//
//  TEraser.h
//  Student Support
//
//  Created by Seth Johnson on 2/6/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  This tool simulates the usage of an Eraser.
//  It has a MConstant mask with a radius of 10.0 (diameter of 21) and an
//  opacity of 1.0 Eraser overrides the colorBlendMath() function to provide its
//  special eraser functionality

#ifndef INCLUDE_TERASER_H_
#define INCLUDE_TERASER_H_

#include "Tool.h"
#include <string>

class TEraser : public Tool {
 public:
        TEraser();

        // overrides super's implementation
        ColorData colorBlendMath(
            float mask,
            ColorData toolColor,
            ColorData canvasColor,
            ColorData backgroundColor);

        std::string getName();
};

#endif  // INCLUDE_TERASER_H_
