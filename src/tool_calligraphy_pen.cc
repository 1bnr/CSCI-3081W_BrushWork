/*******************************************************************************
 * Name            : TCalligraphyPen.cc
 * Project         : BrushWork
 * Module          : ??
 * Description     : Implementation of calligraphy pen  tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "TCalligraphyPen.h"
#include "MOval.h"

#include <string>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
TCalligraphyPen::TCalligraphyPen(void) {
    mask(new MOval(7.0, 1.0, 70.0, 0.333));
}

}  // namespace csci3081
