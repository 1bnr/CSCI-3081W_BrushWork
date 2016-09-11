/*******************************************************************************
 * Name            : TCalliggraphyPen.h
 * Project         : BrushWork
 * Module          : ??
 * Description     : Header file for Calligraphy pen class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_TCALLIGRAPHYPEN_H_
#define INCLUDE_TCALLIGRAPHYPEN_H_

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
//  This tool simulates the usage of a Calligraphy Pen.
//
//  It has a MOval mask with a radius of 7.0 (diameter of 15), an opacity of 1.0
//  (completely opaque), an angle of 70 degrees counter-clockwise from the
//  x-axis, and an elongation ratio of 0.333
class TCalligraphyPen : public Tool {
 public:
        TCalligraphyPen();

        std::string getName();
};
}  // namespace csci3081

#endif  // INCLUDE_TCALLIGRAPHYPEN_H_
