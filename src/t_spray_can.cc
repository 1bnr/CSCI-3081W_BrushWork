/*******************************************************************************
 * Name            : t_spray_can.cc
 * Project         : BrushWok
 * Module          : Tool
 * Description     : Implementation of SprayCan tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/t_spray_can.h"
#include <string>
#include "include/m_linear.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
TSprayCan::TSprayCan(void) { mask(new MLinear(30, 0.2)); }

}  // namespace image_tools
