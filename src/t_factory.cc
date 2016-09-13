/*******************************************************************************
 * Name            : tool_factory.cc
 * Project         : BrushWork
 * Module          : Tool
 * Description     : Implementation of factory design pattern for tools
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "tool_factory.h"
#include "tool.h"
#include "t_pen.h"
#include "t_eraser.h"
#include "t_calligraphy_pen.h"
#include "t_highlighter.h"
#include "t_spray_can.h"
#include "t_chalk.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
Tool* ToolFactory::CreateTool(int toolID) {
  Tool* tool = nullptr;

  switch (toolID) {
    case TOOL_PEN:
      tool = new TPen();
      break;
    case TOOL_ERASER:
      tool = new TEraser();
      break;
    case TOOL_SPRAYCAN:
      tool = new TSprayCan();
      break;
    case TOOL_CALLIGRAPHYPEN:
      tool = new TCalligraphyPen();
      break;
    case TOOL_HIGHLIGHTER:
      tool = new THighlighter();
      break;
    case TOOL_CHALK:
      tool = new TChalk();
      break;
    default:
      tool = nullptr;
      break;
  }

  return tool;
}

}  // namespace csci3081
