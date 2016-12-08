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

#ifndef SRC_APP_FLASHPHOTO_SRC_FLASHPHOTO_APP_H_
#define SRC_APP_FLASHPHOTO_SRC_FLASHPHOTO_APP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
#include "../../../lib/libimgtools/src/include/base_gfx_app.h"
#include "../../../lib/libimgtools/src/include/color_data.h"
#include "../../../lib/libimgtools/src/include/pixel_buffer.h"
#include "../../../lib/libimgtools/src/include/filter_manager.h"
#include "io_manager.h"
#include "../../../lib/libimgtools/src/include/ui_ctrl.h"
#include "../../../lib/libimgtools/src/include/state_manager.h"
#include "../../../lib/libimgtools/src/include/tool.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for FlashPhoto.
 * It is a graphics app that derives from BaseGfxApp. It creates two graphics
 * windows, one for 2D painting and one for the buttons and other UI widgets to
 * control the brushes.
 **/
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
   * @brief Update the colors displayed on the GLUI control panel after updating
   * their values in FlashPhoto
   *
   */
  void update_colors(void);

  /**
   * @brief Initialize the GLUI interface
   *
   */
  void InitGlui(void);

  /**
   * @brief Initialize OpenGL
   *
   */
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
   * @brief Manager for all filter operations
   */
  FilterManager filter_manager_;

  /**
   * @brief Manager for all I/O operations
   */
  IOManager io_manager_;

  /**
   * @brief Manager for redo/undo stack
   */
  StateManager state_manager_;

  /**
   * @brief A collection of GLUI spinners for RGB control elements.
   */
  struct {
    GLUI_Spinner *spinner_red;
    GLUI_Spinner *spinner_green;
    GLUI_Spinner *spinner_blue;
  } glui_ctrl_hooks_;

  /** Pointer to pixel data for the screen */
  PixelBuffer *display_buffer_;

  /** Pointer to pixel data for the stamp */
  PixelBuffer *stamp_buffer_;

  int cur_tool_; /**< Currently selected tool from UI  */
  std::vector<Tool*> tools_;

  /** List of Pixel Buffers for the state manager */
  std::vector<PixelBuffer*> states_;
  unsigned int cur_state_ = 0;  // Holds the index of the PixelBuffer being displayed

  // Previous mouse coordinates for interpreting mouse moves
  int mouse_last_x_;
  int mouse_last_y_;
  float cur_color_red_;
  float cur_color_green_;
  float cur_color_blue_;

  GLUI_Spinner *spinner_r_; /**< Hook for accessing the UI red amount  */
  GLUI_Spinner *spinner_g_; /**< Hook for accessing the UI green amount  */
  GLUI_Spinner *spinner_b_; /**< Hook for accessing the UI blue amount  */

  /** TODO implement undo queue */
  void add_buffer_to_undo_stack(PixelBuffer* &current_buffer);

  void maintain_states_stack(unsigned int cur_state);

  void printStack();
};

}  /* namespace image_tools */

#endif  // SRC_APP_FLASHPHOTO_SRC_FLASHPHOTO_APP_H_
