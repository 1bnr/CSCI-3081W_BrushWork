/*******************************************************************************
 * Name            : mia_app.cc
 * Project         : MIA
 * Module          : App
 * Description     : Implementation of MIA
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 12/07/16
 * Original Author : Team 0x07
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app/MIA/src/include/mia_app.h"
#include <assert.h>
#include <cmath>
#include <string>
#include <iostream>
#include "../../../lib/libimgtools/src/include/color_data.h"
#include "../../../lib/libimgtools/src/include/pixel_buffer.h"
#include "../../../lib/libimgtools/src/include/ui_ctrl.h"
#include "../../../lib/libimgtools/src/include/tool_factory.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MIAApp::MIAApp(int width, int height, const std::string &marker_fname) :
                                              BaseGfxApp(width, height),
                                              filter_manager_(),
                                              io_manager_(),
                                              state_manager_(),
                                              // glui_ctrl_hooks_(),
                                              display_buffer_(nullptr),
                                              stamp_buffer_(nullptr),
                                              cur_tool_(0),
                                              tools_(),
                                              states_(0),
                                              marker_fname_(marker_fname),
                                              mouse_last_x_(0),
                                              mouse_last_y_(0) {}
MIAApp::~MIAApp(void) {
  if (display_buffer_) {
    delete display_buffer_;
  }
  if (stamp_buffer_) {
    delete stamp_buffer_;
  }
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MIAApp::Init(
    int argc,
    char* argv[],
    int x,
    int y,
    ColorData background_color) {
  BaseGfxApp::Init(argc, argv,
                   x, y,
                   GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH,
                   true,
                   width()+51,
                   50);

  // Set the name of the window
  set_caption("MIA");

  // Initialize Interface
  InitializeBuffers(background_color, width(), height());

  // Create array of Tools to have marker and stamp
  Tool* pen = ToolFactory::CreateTool(0);
  assert(pen);
  tools_.push_back(pen);
  Tool* marker = ToolFactory::CreateTool(6);
  assert(marker);
  tools_.push_back(marker);


  InitGlui();
  InitGraphics();
}

void MIAApp::Display(void) {
  DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

void MIAApp::MouseMoved(int x, int y) {}

void MIAApp::MouseDragged(int x, int y) {
  /* Stamp is not a draggable tool */
  if (tools_[cur_tool_]->name() == "Stamp")
    return;
  int max_steps = 30;

  // We implimented a smoothing feature by interpolating between
  // mouse events. This is at the expense of processing, though,
  // because we just "stamp" the tool many times between the two
  // even locations. you can reduce max_steps until it runs
  // smoothly on your machine.

  // Get the differences between the events
  // in each direction
  int delta_x = x-mouse_last_x_;
  int delta_y = y-mouse_last_y_;

  // Calculate the min number of steps necesary to fill
  // completely between the two event locations.
  float pixels_between = fmax(abs(delta_x), abs(delta_y));
  int step_size = 1;

  // Optimize by maxing out at the max_steps,
  // and fill evenly between
  if (pixels_between > max_steps) {
    step_size = pixels_between/max_steps;
  }

  // Iterate between the event locations
  for (int i = 0; i < pixels_between; i+=step_size) {
    int curr_x = mouse_last_x_+(i*delta_x/pixels_between);
    int curr_y = mouse_last_y_+(i*delta_y/pixels_between);

    tools_[cur_tool_]->ApplyToBuffer(curr_x, height()-curr_y,
                                     ColorData(1, 0, 0),
                                     display_buffer_,
                                     stamp_buffer_);
  }

  // let the previous point catch up with the current.
  mouse_last_x_ = x;
  mouse_last_y_ = y;
}

void MIAApp::LeftMouseDown(int x, int y) {
  std::cout << cur_tool_ << std::endl;
  maintain_states_stack(cur_state_);
  add_buffer_to_undo_stack();
  tools_[cur_tool_]->ApplyToBuffer(x, height()-y,
                                   ColorData(1, 0, 0),
                                   display_buffer_,
                                   stamp_buffer_);
  mouse_last_x_ = x;
  mouse_last_y_ = y;
}

void MIAApp::LeftMouseUp(int x, int y) {
  std::cout << "mouseReleased " << x << " " << y << std::endl;
}

void MIAApp::InitializeBuffers(ColorData background_color,
                                      int width, int height) {
  display_buffer_ = new PixelBuffer(width, height, background_color);
  // Add initial blank state
  states_.push_back(display_buffer_);
  PixelBuffer * mb;  // new buffer
  mb = io_manager_.InitStamp(marker_fname_);
  // Set the stamp buffer to NULL; check before applying
  stamp_buffer_ = mb;
}

void MIAApp::InitGlui(void) {
  // Select first tool (this activates the first radio button in glui)
  cur_tool_ = 0;

  new GLUI_Column(glui(), false);
  GLUI_Panel *tool_panel = new GLUI_Panel(glui(), "Tool Type");
  {
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(tool_panel, &cur_tool_,
                                                 UICtrl::UI_TOOLTYPE,
                                                 s_gluicallback);
    // Create interface buttons for different tools:
    new GLUI_RadioButton(radio, "Pen");
    new GLUI_RadioButton(radio, "Marker");
  }

  /* Initialize state management (undo, redo, quit) */
  state_manager_.InitGlui(glui(), s_gluicallback);

  new GLUI_Button(const_cast<GLUI*>(glui()),
                  "Quit", UICtrl::UI_QUIT,
                  static_cast<GLUI_Update_CB>(exit));

  /* Initialize Filtering */
  filter_manager_.InitGlui(glui(), s_gluicallback);

  /* Initialize image I/O */
  io_manager_.InitGlui(glui(), s_gluicallback);
  return;
}

void MIAApp::GluiControl(int control_id) {
  switch (control_id) {
    case UICtrl::UI_APPLY_BLUR:
      maintain_states_stack(cur_state_);
      // Save the new buffer with the image to the undo state
      add_buffer_to_undo_stack();
      filter_manager_.ApplyBlur(display_buffer_);
      break;
    case UICtrl::UI_APPLY_SHARP:
      maintain_states_stack(cur_state_);
      // Save the new buffer with the image to the undo state
      add_buffer_to_undo_stack();
      filter_manager_.ApplySharpen(display_buffer_);
      break;
    case UICtrl::UI_APPLY_MOTION_BLUR:
      maintain_states_stack(cur_state_);
      // Save the new buffer with the image to the undo state
      add_buffer_to_undo_stack();
      filter_manager_.ApplyMotionBlur(display_buffer_);
      break;
    case UICtrl::UI_APPLY_EDGE:
      maintain_states_stack(cur_state_);
      add_buffer_to_undo_stack();
      filter_manager_.ApplyEdgeDetect(display_buffer_);
      break;
    case UICtrl::UI_APPLY_THRESHOLD:
      maintain_states_stack(cur_state_);
      // Save the new buffer with the image to the undo state
      add_buffer_to_undo_stack();
      filter_manager_.ApplyThreshold(display_buffer_);  // updating new buffer
      break;
    case UICtrl::UI_APPLY_SATURATE:
      maintain_states_stack(cur_state_);
      // Save the new buffer with the image to the undo state
      add_buffer_to_undo_stack();
      filter_manager_.ApplyGrayscale(display_buffer_);
      break;
    case UICtrl::UI_APPLY_QUANTIZE:
      maintain_states_stack(cur_state_);
      // Save the new buffer with the image to the undo state
      add_buffer_to_undo_stack();
      filter_manager_.ApplyQuantize(display_buffer_);
      break;
    case UICtrl::UI_FILE_BROWSER:
      io_manager_.set_image_file(io_manager_.file_browser()->get_file());
      break;
    case UICtrl::UI_LOAD_CANVAS_BUTTON:
      std::cout << "REDO CLICKED" << std::endl;
      PixelBuffer * nb;  // new buffer
      nb = io_manager_.LoadImageToCanvas();
      // if image loaded successfully, send it to the display
      if (nb != NULL) {
        // Set the window dimensions to the state that was just restored
        SetWindowDimensions(nb->width(), nb->height());
        display_buffer_ = nb;
        // Handle the case which we are not at the end of the undo stack
        maintain_states_stack(cur_state_);
        // Save the new buffer with the image to the undo state
        add_buffer_to_undo_stack();
      }
      break;
    case UICtrl::UI_SAVE_CANVAS_BUTTON:
      io_manager_.SaveCanvasToFile(display_buffer_, io_manager_.file_name());
      // Reload the current directory:
      io_manager_.file_browser()->fbreaddir(".");
      break;
    case UICtrl::UI_NEXT_IMAGE_BUTTON:
      io_manager_.LoadNextImage();
      PixelBuffer * ni;  // new buffer
      ni = io_manager_.LoadImageToCanvas();
      // if image loaded successfully, send it to the display
      if (ni != NULL) {
        // Set the window dimensions to the state that was just restored
        SetWindowDimensions(ni->width(), ni->height());
        display_buffer_ = ni;
        // Handle the case which we are not at the end of the undo stack
        maintain_states_stack(cur_state_);
        // Save the new buffer with the image to the undo state
        add_buffer_to_undo_stack();
      }
      break;
    case UICtrl::UI_PREV_IMAGE_BUTTON:
      io_manager_.LoadPreviousImage();
      PixelBuffer * pi;  // new buffer
      pi = io_manager_.LoadImageToCanvas();
      // if image loaded successfully, send it to the display
      if (pi != NULL) {
        // Set the window dimensions to the state that was just restored
        SetWindowDimensions(pi->width(), pi->height());
        display_buffer_ = pi;
        // Handle the case which we are not at the end of the undo stack
        maintain_states_stack(cur_state_);
        // Save the new buffer with the image to the undo state
        add_buffer_to_undo_stack();
      }
      break;
    case UICtrl::UI_FILE_NAME:
      io_manager_.set_image_file(io_manager_.file_name());
      break;
    case UICtrl::UI_UNDO:
      std::cout << "UNDO CLICKED" << std::endl;
      display_buffer_ = states_[cur_state_-1];
      cur_state_-= 1;  // Decrement the current index after undoing
      // Set the window dimensions to the state that was just restored
      SetWindowDimensions(display_buffer_->width(), display_buffer_->height());
      // Check if the undo button should be disabled (no more states)
      if (cur_state_ > 0) {
        state_manager_.undo_toggle(true);
      } else {
        state_manager_.undo_toggle(false);
      }
      // Check if the redo button should be enabled
      if (cur_state_ != states_.size()-1) {
        state_manager_.redo_toggle(true);
      } else {
        state_manager_.redo_toggle(false);
      }
      break;
    case UICtrl::UI_REDO:
      std::cout << "REDO CLICKED" << std::endl;
      display_buffer_ = states_[cur_state_+1];
      cur_state_ += 1;
      SetWindowDimensions(display_buffer_->width(), display_buffer_->height());
      // Check if the redo button should be enabled
      // Handle the case which we are not at the end of the undo stack
      if (cur_state_ != states_.size()-1) {
        state_manager_.redo_toggle(true);
      } else {
        state_manager_.redo_toggle(false);
      }
      if (cur_state_ > 0) {
        state_manager_.undo_toggle(true);
      } else {
        state_manager_.undo_toggle(false);
      }
      break;
    default:
      break;
  }

  // Forces canvas to update changes made in this function
  glui()->post_update_main_gfx();
}

/*******************************************************************************
 * Member Functions For Managing GLUI Interface
 ******************************************************************************/

void MIAApp::InitGraphics(void) {
  // Initialize OpenGL for 2D graphics as used in the FlashPhoto app
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(0, width(), 0, height());
  glViewport(0, 0, width(), height());
}
// Handles adding states to the states_ stack and incrementing the cur_state_
void MIAApp::add_buffer_to_undo_stack() {
  PixelBuffer* old_buffer = new PixelBuffer(*display_buffer_);
  states_.push_back(old_buffer);
  cur_state_ += 1;  // Update index
  display_buffer_ = states_[cur_state_];
  if (cur_state_ > 0) {
    state_manager_.undo_toggle(true);
  }
}

// Handles the case in which we undo and then draw, we need to erase
// any states after this point because they are overwritten
void MIAApp::maintain_states_stack(unsigned int cur_state) {
  if (cur_state != states_.size()-1) {
    states_.erase(states_.begin()+cur_state+1, states_.end());
    state_manager_.redo_toggle(false);  // again handle toggle
  }
}

// Function to print out the stack (for debugging purposes)
void MIAApp::printStack() {
  if (states_.size() == 0) {
  } else {
    std::cout << "------The Undo Stack-----" << "cur_state_: "
    << cur_state_ << "  display_buffer_:  " << display_buffer_ << std::endl;
    for (unsigned int i = 0; i < states_.size(); i++) {
      std::cout << "|   " << i << "   |   " << states_[i] << "   | "
      << "Width, Height: " << states_[i]->width() << ", "
      << states_[i]->height() << std::endl;
    }
  std::cout << "------End of Stack-----" << std::endl;
  }
}

}  /* namespace image_tools */
