/*******************************************************************************
 * Name            : ToolFactory.cc
 * Project         : BrushWork
 * Module          : ??
 * Description     : Implementation of factory design pattern for tools
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "ToolFactory.h"
#include "Tool.h"
#include "Tool_Pen.h"
#include "Tool_Eraser.h"
#include "Tool_CalligraphyPen.h"
#include "Tool_Highlighter.h"
#include "Tool_SprayCan.h"
#include "Tool_Chalk.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace csci3081 {

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
