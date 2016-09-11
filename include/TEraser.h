/*******************************************************************************
 * Name            : TEraser.h
 * Project         : BrushWork
 * Module          : ??
 * Description     : Header file for Eraserclass
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_TERASER_H_
#define INCLUDE_TERASER_H_

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
//  This tool simulates the usage of an Eraser.
//  It has a MConstant mask with a radius of 10.0 (diameter of 21) and an
//  opacity of 1.0 Eraser overrides the colorBlendMath() function to provide its
//  special eraser functionality
class TEraser : public Tool {
 public:
        TEraser();

        // overrides super's implementation
        ColorData colorBlendMath(
            float mask,
            ColorData toolColor,
            ColorData canvasColor,
            ColorData backgroundColor);

        std::string getName();
};
}  // namespace csci3081

#endif  // INCLUDE_TERASER_H_
