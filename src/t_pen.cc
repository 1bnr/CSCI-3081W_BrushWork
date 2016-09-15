/*******************************************************************************
 * Name            : t_pen.cc
 * Project         : BrushWork
 * Module          : Tool
 * Description     : Implementation of Pen tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/t_pen.h"
#include <string>
#include "include/m_constant.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
TPen::TPen(void) { mask(new MConstant(1.0, 1.0)); }

}  // namespace image_tools
