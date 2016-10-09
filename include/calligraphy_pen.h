/*******************************************************************************
 * Name            : calligraphy_pen.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Calligraphy Pen class.
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 10/06/16
 * Original Author : Ben Bramanti
 *
 ******************************************************************************/

#ifndef INCLUDE_CALLIGRAPHY_PEN_H_
#define INCLUDE_CALLIGRAPHY_PEN_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/base_gfx_app.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include "include/tool.h"

 /*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is the header file for the calligrahy pen tool.
 */
class CalligraphyPen : public Tool {
 public:
   CalligraphyPen();
   virtual ~CalligraphyPen();

 private:

};
}  // namespace image_tools
#endif  // INCLUDE_CALLIGRAPHY_PEN_H_