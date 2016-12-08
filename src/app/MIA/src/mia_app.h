/*******************************************************************************
> * Name            : mia_app.h
 * Project         : MIA
 * Module          : App
 * Description     : Header file for MIA class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 5/15/15
 * Original Author : Team 0x07
 *
 ******************************************************************************/

#ifndef SRC_APP_MIA_SRC_MIA_APP_H_
#define SRC_APP_MIA_SRC_MIA_APP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
#include "../../../lib/libimgtools/src/include/base_gfx_app.h"
#include "../../../lib/libimgtools/src/include/color_data.h"
#include "../../../lib/libimgtools/src/include/pixel_buffer.h"
#include "mia_filter_manager.h"
#include "mia_io_manager.h"
#include "../../../lib/libimgtools/src/include/io_manager.h"
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
class MIAApp : public BaseGfxApp {
 public:
  MIAApp(int width, int height, std::string marker_fname);
  virtual ~MIAApp(void);

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
  MIAApp(const MIAApp &rhs) = delete;
  MIAApp& operator=(const MIAApp &rhs) = delete;

  /**
   * @brief Manager for all filter operations
   */
  MIAFilterManager filter_manager_;

  /**
   * @brief Manager for all I/O operations
   */
  MIAIOManager io_manager_;

  /**
   * @brief Manager for redo/undo stack
   */
  StateManager state_manager_;


  /** Pointer to pixel data for the screen */
  PixelBuffer *display_buffer_;

  /** Pointer to pixel data for the stamp */
  PixelBuffer *stamp_buffer_;

  int cur_tool_; /**< Currently selected tool from UI  */
  std::vector<Tool*> tools_;

  /** List of Pixel Buffers for the state manager */
  std::vector<PixelBuffer*> states_;
  unsigned int cur_state_ = 0;  // Holds the index of the PixelBuffer being displayed


  // The path to the marker file
  std::string marker_fname_;

  // Previous mouse coordinates for interpreting mouse moves
  int mouse_last_x_;
  int mouse_last_y_;

  /** TODO implement undo queue */
  void add_buffer_to_undo_stack(PixelBuffer* &current_buffer);

  void maintain_states_stack(unsigned int cur_state);

  void printStack();
};

}  /* namespace image_tools */

#endif  // SRC_APP_MIA_SRC_MIA_APP_H_
