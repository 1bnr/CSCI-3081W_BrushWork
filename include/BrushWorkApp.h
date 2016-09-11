/*******************************************************************************
 * Name            : BrushWorkApp.h
 * Project         : BrushWork
 * Module          : ??
 * Description     : Header file for BrushWork application.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/


#ifndef INCLUDE_BRUSHWORKAPP_H_
#define INCLUDE_BRUSHWORKAPP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "BaseGfxApp.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "Tool.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace csci3081 {
namespace brushwork {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * This is the main class for BrushWork.  It is a graphics app that derives
 * from BaseGfxApp. It creates two graphics windows, one for 2D painting and
 * one for the buttons and other UI widgets to control the brushes.
 **/
class BrushWorkApp : public csci3081::BaseGfxApp {
 public:
  BrushWorkApp(
      int width,
      int height);

  virtual ~BrushWorkApp(void);

  // Glut overrided function
  void MouseDragged(int x, int y);
  void MouseMoved(int x, int y);
  void LeftMouseDown(int x, int y);
  void LeftMouseUp(int x, int y);
  void Display(void);
  void GluiControl(int controlID);

  virtual void Init(
      int argc,
      char* argv[],
      int x,
      int y,
      ::csci3081::ColorData backgroundColor);

 private:
  // BrushWork-specific functions
  void InitGlui(void);
  void InitGraphics(void);
  void InitializeBuffers(::csci3081::ColorData initialColor, int width, int height);

  // GLUI INTERFACE ELEMENTS
  enum UIControlType {
    UI_TOOLTYPE,
    UI_COLOR_R,
    UI_COLOR_G,
    UI_COLOR_B,
    UI_PRESET_RED,
    UI_PRESET_ORANGE,
    UI_PRESET_YELLOW,
    UI_PRESET_GREEN,
    UI_PRESET_BLUE,
    UI_PRESET_PURPLE,
    UI_PRESET_WHITE,
    UI_PRESET_BLACK,
    UI_QUIT
  };

  // Pointer to the buffer where the display PixelBuffer is stored
  csci3081::PixelBuffer *display_buffer_;

  // These are used to store the selections from the GLUI user interface
  // These are used to store the selections from the GLUI user interface
  int cur_tool_;
  csci3081::Tool **tools_;

  // Previous mouse coordinates for interpreting mouse moves
  int mouse_last_x_;
  int mouse_last_y_;

  float cur_color_red_;
  float cur_color_green_;
  float cur_color_blue_;

  GLUI_Spinner *spinner_r_;
  GLUI_Spinner *spinner_g_;
  GLUI_Spinner *spinner_b_;

  // Copy assignment/construction disallowed
  BrushWorkApp(const BrushWorkApp &rhs) = delete;
  BrushWorkApp& operator=(const BrushWorkApp &rhs) = delete;
};
}  // namespace brushwork
}  // namespace csci3081

#endif  // INCLUDE_BRUSHWORKAPP_H_
