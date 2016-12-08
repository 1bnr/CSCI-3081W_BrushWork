/*******************************************************************************
 * Name            : mia_state_manager.h
 * Project         : FlashPhoto
 * Module          : state_manager
 * Description     : Header for IoHandler class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 20:40:20 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

#ifndef SRC_APP_FLASHPHOTO_SRC_MIA_STATE_MANAGER_H_
#define SRC_APP_FLASHPHOTO_SRC_MIA_STATE_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "../../FlashPhoto/src/state_manager.h"
#include <string>
#include <vector>
#include "GL/glui.h"
#include "../../FlashPhoto/src/ui_ctrl.h"
#include "../../../lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The manager for simulation state in FlashPhoto.
 *
 * Simulation state is defined as the sequence of operations that comprises the
 * current canvas. An operation is defined as what happens during 1 click/drag
 * operation, or when 1 button on the control panel that affects the canvas is
 * clicked.
 *
 * A sequence of undos followed by some edits, followed by more undos will
 * FIRST undo the new edits, until you get back to the state before you made the
 * edits. You will not be able to go back any further.
 */
class MIAStateManager : public StateManager {
 public:
  MIAStateManager();
  ~MIAStateManager() {}

  void InitGlui(const GLUI *const glui,
                void (*s_gluicallback)(int));

  /**
   * @brief Undoes the last operation applied to the canvas (not permanently; it
   * can still be re-done later)
   *
   */
  void UndoOperation(PixelBuffer* &display_buffer,
                     std::vector<PixelBuffer*> states_, int cur_state_);

  /**
   * @brief Re-does the last un-done operation applied to the canvas (not
   * permanently; it can be undone again later)
   *
   */
  void RedoOperation(PixelBuffer* &display_buffer,
                     std::vector<PixelBuffer*> states_, int cur_state_);

  void redo_toggle(bool select) {
    UICtrl::button_toggle(redo_btn_, select);
  }

  void undo_toggle(bool select) {
    UICtrl::button_toggle(undo_btn_, select);
  }

 private:
  /* Copy/move assignment/construction disallowed */
  MIAStateManager(const MIAStateManager &rhs) = delete;
  MIAStateManager& operator=(const MIAStateManager &rhs) = delete;

  /* data members */
  GLUI_Button *undo_btn_;
  GLUI_Button *redo_btn_;
};

}  /* namespace image_tools */

#endif  /* SRC_APP_MIA_SRC_MIA_STATE_MANAGER_H_ */
