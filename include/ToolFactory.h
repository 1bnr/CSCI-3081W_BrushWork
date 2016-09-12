/*******************************************************************************
 * Name            : ToolFactory.h
 * Project         : csci3081
 * Module          : Tool
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Description     : Header file for ToolFactoryppp
  * Creation Data   : 2/15/15
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
/**
 * @brief Implementation of factory pattern to handle tool creation
 * This enables easy extension/addition of new tools.
 */
class ToolFactory {
 public:
  /**
   * @brief The list of tools that can be created by the factory and used by the
   * application
   */
  enum TOOLS {
    TOOL_PEN = 0,
    TOOL_ERASER = 1,
    TOOL_SPRAYCAN = 2,
    TOOL_CALLIGRAPHYPEN = 3,
    TOOL_HIGHLIGHTER = 4,
    TOOL_CHALK = 5,
    NUMTOOLS = 6
  };

  /**
   * @brief Return the total # of tools in the application
   */
  static int num_tools(void) { return NUMTOOLS; }

  /**
   * @brief Create a tool from the list of defined tools
   * @return The initialized tool, or nullptr if an invalid index was passed
   */
  static Tool* CreateTool(int toolID);
};
}  // namespace csci3081

#endif  // INCLUDE_TOOLFACTORY_H_
