/*******************************************************************************
 * Name            : ToolFactory.h
 * Project         : csci3081
 * Module          : ??
 * Description     : Header file for ToolFactory
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_TOOLFACTORY_H_
#define INCLUDE_TOOLFACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Tool.h"
#include <vector>

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
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

    static int num_tools(void) { return NUMTOOLS; }
    static Tool* CreateTool(int toolID);
};
}  // namespace csci3081

#endif  // INCLUDE_TOOLFACTORY_H_
