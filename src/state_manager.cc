/*******************************************************************************
 * Name            : state_manager.cc
 * Project         : FlashPhoto
 * Module          : state_manager
 * Description     : Implementation of StateManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Sun Oct 2 20:47:05 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/state_manager.h"
#include <iostream>
#include "include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
StateManager::StateManager(void) :
    undo_btn_(nullptr),
    redo_btn_(nullptr) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void StateManager::InitGlui(const GLUI *const glui,
                            void (*s_gluicallback)(int)) {
  undo_btn_ = new GLUI_Button(const_cast<GLUI*>(glui), "Undo", UICtrl::UI_UNDO,
                              s_gluicallback);
  undo_toggle(false);

  redo_btn_  = new GLUI_Button(const_cast<GLUI*>(glui), "Redo", UICtrl::UI_REDO,
                               s_gluicallback);
  redo_toggle(false);
}

void StateManager::UndoOperation(PixelBuffer* display_buffer, std::vector<PixelBuffer> states_, int cur_state_) {
  std::cout << "Undoing..." << std::endl;
  // Sets the display_buffer to the previous state
  *display_buffer = states_[cur_state_-1];
  std::cout << "State: " << cur_state_-1 << " " << &states_[cur_state_-1] << std::endl;
}

void StateManager::RedoOperation(PixelBuffer* display_buffer, std::vector<PixelBuffer> states_, int cur_state_) {
  std::cout << "Redoing..." << std::endl;
  //sets the display_buffer to the state before the undo call
  *display_buffer = states_[cur_state_+1];
  std::cout << "State: " << cur_state_+1 << " " << &states_[cur_state_+1] << std::endl;
}

}  /* namespace image_tools */
