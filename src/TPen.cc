/*******************************************************************************
 * Name            : TPen.cc
 * Project         : BrushWork
 * Module          : ??
 * Description     : Implementation of Pen tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "TPen.h"
#include "MConstant.h"

#include <string>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
TPen::TPen(void) {
  m_mask = new MConstant(1.0, 1.0);
}

}  // namespace csci3081
