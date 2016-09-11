/*******************************************************************************
 * Name            : TSprayCan.h
 * Project         : csci3081
 * Module          : ??
 * Description     : Header file for SprayCan tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_TSPRAYCAN_H_
#define INCLUDE_TSPRAYCAN_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Tool.h"
#include <string>

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class TSprayCan : public Tool {
 public:
  TSprayCan(void);

  std::string name(void) { return "Spray Can"; }
};
}  // namespace csci3081

#endif  // INCLUDE_TSPRAYCAN_H_
