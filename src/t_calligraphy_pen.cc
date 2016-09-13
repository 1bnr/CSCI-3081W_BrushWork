/*******************************************************************************
 * Name            : t_calligraphy_pen.cc
 * Project         : BrushWork
 * Module          : Tool
 * Description     : Implementation of calligraphy pen  tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "t_calligraphy_pen.h"
#include "m_oval.h"

#include <string>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
TCalligraphyPen::TCalligraphyPen(void) {
    mask(new MOval(7.0, 1.0, 70.0, 0.333));
}

}  // namespace csci3081
