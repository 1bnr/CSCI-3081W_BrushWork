/*******************************************************************************
 * Name            : flashphoto_app.h
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Header file for FlashPhotoApp class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_FLASHPHOTO_APP_H_
#define INCLUDE_FLASHPHOTO_APP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "include/base_gfx_app.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include "include/filter_manager.h"
#include "include/io_manager.h"
#include "include/ui_ctrl.h"
#include "include/state_manager.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class FlashPhotoApp : public BaseGfxApp {
 public:
  FlashPhotoApp(int width, int height);
  virtual ~FlashPhotoApp(void);

  void MouseDragged(int x, int y);
  void MouseMoved(int x, int y);
  void LeftMouseDown(int x, int y);
  void LeftMouseUp(int x, int y);
  void Display(void);
  void GluiControl(int control_id);
  /**
   * @brief Initialize the FlashPhotoApp
   *
   * @param[in] argc Unused--required by BaseGfxApp
   * @param[in] argv Unused--required by BaseGfxApp
   * @param[in] x Unused--required by BaseGfxApp
   * @param[in] y Unused--required by BaseGfxApp
   * @param[in] background_color The initial canvas color
   */
  void Init(
      int argc,
      char *argv[],
      int x,
      int y,
      ColorData background_color);

 private:
  /**
   * @brief Update the colors displayed on the GLUI control panel
   * TODO: is this correct
   *
   */
  void update_colors(void);

  void InitGlui(void);
  void InitGraphics(void);

  /**
   * @brief Initialize the buffers for the main window
   */
  void InitializeBuffers(ColorData initial_color,
                         int width, int height);

  /* Copy/move assignment/construction disallowed */
  FlashPhotoApp(const FlashPhotoApp &rhs) = delete;
  FlashPhotoApp& operator=(const FlashPhotoApp &rhs) = delete;

  /**
   * @brief TODO: Fill this in
   */
  enum UIMotionBlurDirections {
    DIR_N_S,
    DIR_E_W,
    DIR_NE_SW,
    DIR_NW_SE
  };

  /**
   * @brief A collection of filter parameters/operations for manipulating photos
   * TODO: Add more detail
   */
  FilterManager filter_manager_;

  /**
   * @brief A collection of I/O parameters for manipulating photos
   * TODO: Add more detail
   */
  IOManager io_manager_;

  /**
   * @brief Manager for redo/undo stack
   * TODO: Add more detail
   */
  StateManager state_manager_;

  /**
   * @brief A collection of various GLUI control elements.
   * TODO: Add more detail, and add comments/doc for the members below
   */
  struct {
    GLUI_Spinner *spinner_red;
    GLUI_Spinner *spinner_green;
    GLUI_Spinner *spinner_blue;
  } glui_ctrl_hooks_;

  /** Pointer to pixel data for the screen */
  PixelBuffer *display_buffer_;

  // These are used to store the selections from the GLUI user interface
  int cur_tool_;  /**< Currently selected tool from UI */
  float cur_color_red_;
  float cur_color_green_;
  float cur_color_blue_;
};
}  // namespace image_tools

#endif  // INCLUDE_FLASHPHOTO_APP_H_
