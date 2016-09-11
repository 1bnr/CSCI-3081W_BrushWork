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
#include "TPen.h"
#include "TEraser.h"
#include "TCalligraphyPen.h"
#include "THighlighter.h"
#include "TSprayCan.h"
#include "TChalk.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
int ToolFactory::getNumTools() {
        return NUMTOOLS;
}

Tool* ToolFactory::createTool(int toolID) {
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
