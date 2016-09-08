//
//  ToolFactory.h
//  Student Support
//
//  Created by Seth Johnson on 2/6/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#ifndef INCLUDE_TOOLFACTORY_H_
#define INCLUDE_TOOLFACTORY_H_

#include "Tool.h"
#include <vector>

class ToolFactory {
 public:
        enum TOOLS {
                TOOL_PEN = 0,
                TOOL_ERASER = 1,
                TOOL_SPRAYCAN = 2,
                TOOL_CALLIGRAPHYPEN = 3,
                TOOL_HIGHLIGHTER = 4,
                TOOL_CHALK = 5,
                NUMTOOLS = 6
        };

        static int getNumTools();
        static Tool* createTool(int toolID);
};

#endif  // INCLUDE_TOOLFACTORY_H_
