/*******************************************************************************
 * Name            : TPen.h
 * Project         : csci3081
 * Module          : ??
 * Description     : Header file for Pen tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/
#ifndef INCLUDE_TPEN_H_
#define INCLUDE_TPEN_H_

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
//  This tool simulates the usage of a Pen.
//  It has a MConstant mask with a radius of 1.0 (diameter of 3) and an opacity
//  of 1.0

class TPen : public Tool {
 public:
        TPen();
        std::string getName();
};
}  // namespace csci3081

#endif  // INCLUDE_TPEN_H_
