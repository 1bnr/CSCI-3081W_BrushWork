/*******************************************************************************
 * Name            : flashphoto_app.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of FlashPhoto
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/flashphoto_app.h"
#include <cmath>
#include <iostream>
#include <assert.h>
#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include "include/ui_ctrl.h"
#include "include/tool_factory.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FlashPhotoApp::FlashPhotoApp(int width, int height) : BaseGfxApp(width, height),
                                                      filter_manager_(),
                                                      io_manager_(),
                                                      state_manager_(),
                                                      glui_ctrl_hooks_(),
                                                      display_buffer_(nullptr),
                                                      cur_tool_(0),
                                                      tools_(),
                                                      mouse_last_x_(0),
                                                      mouse_last_y_(0),
                                                      cur_color_red_(0.0),
                                                      cur_color_green_(0.0),
                                                      cur_color_blue_(0.0),
                                                      spinner_r_(nullptr),
                                                      spinner_g_(nullptr),
                                                      spinner_b_(nullptr) {}
FlashPhotoApp::~FlashPhotoApp(void) {
  if (display_buffer_) {
    delete display_buffer_;
  }
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void FlashPhotoApp::Init(
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
  set_caption("FlashPhoto");

  // Initialize Interface
  InitializeBuffers(background_color, width(), height());

  // Create array of tools and populate
  for (int i = 0; i < ToolFactory::num_tools(); i++) {
    Tool* t = ToolFactory::CreateTool(i);
    assert(t);
    tools_.push_back(t);
  }
  InitGlui();
  InitGraphics();
}

void FlashPhotoApp::Display(void) {
  DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

void FlashPhotoApp::MouseMoved(int x, int y) {}

void FlashPhotoApp::MouseDragged(int x, int y) {

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
                                     ColorData(cur_color_red_,
                                               cur_color_green_,
                                               cur_color_blue_),
                                     display_buffer_);
  }

  // let the previous point catch up with the current.
  mouse_last_x_ = x;
  mouse_last_y_ = y;
}

void FlashPhotoApp::LeftMouseDown(int x, int y) {
  maintain_states_stack(cur_state_);
  add_buffer_to_undo_stack(display_buffer_);
  tools_[cur_tool_]->ApplyToBuffer(x, height()-y,
                                   ColorData(cur_color_red_,
                                             cur_color_green_,
                                             cur_color_blue_),
                                   display_buffer_);
  mouse_last_x_ = x;
  mouse_last_y_ = y;
}



void FlashPhotoApp::LeftMouseUp(int x, int y) {
  std::cout << "mouseReleased " << x << " " << y << std::endl;
  //std::cout << "Current state: " << cur_state_ << std::endl;
  // Handle the case which we are not at the end of the undo stack
  std::cout << "End Pos: " << states_.size()-1 << std::endl;
  // Save the state of the current pixel buffer before making changes
  //add_buffer_to_undo_stack(display_buffer_);
}

void FlashPhotoApp::InitializeBuffers(ColorData background_color,
                                      int width, int height) {
  display_buffer_ = new PixelBuffer(width, height, background_color);
  //add_buffer_to_undo_stack(display_buffer_); // Add initial blank state
  states_.push_back(display_buffer_);
}

void FlashPhotoApp::InitGlui(void) {
  // Select first tool (this activates the first radio button in glui)
  cur_tool_ = 0;

  GLUI_Panel *tool_panel = new GLUI_Panel(glui(), "Tool Type");
  GLUI_RadioGroup *radio = new GLUI_RadioGroup(tool_panel,
                                               &cur_tool_,
                                               UICtrl::UI_TOOLTYPE,
                                               s_gluicallback);

  // Create interface buttons for different tools:
  for (int i = 0; i < ToolFactory::num_tools(); ++i) {
    new GLUI_RadioButton(radio, tools_[i]->name().c_str());
  }

  GLUI_Panel *color_panel = new GLUI_Panel(glui(), "Tool Color");
  {
    cur_color_red_ = 0;
    glui_ctrl_hooks_.spinner_red  = new GLUI_Spinner(color_panel, "Red:",
                                                     &cur_color_red_,
                                                     UICtrl::UI_COLOR_R,
                                                     s_gluicallback);
    glui_ctrl_hooks_.spinner_red->set_float_limits(0, 1.0);

    cur_color_green_ = 0;
    glui_ctrl_hooks_.spinner_green = new GLUI_Spinner(color_panel, "Green:",
                                                      &cur_color_green_,
                                                      UICtrl::UI_COLOR_G,
                                                      s_gluicallback);
    glui_ctrl_hooks_.spinner_green->set_float_limits(0, 1.0);

    cur_color_blue_ = 0;
    glui_ctrl_hooks_.spinner_blue  = new GLUI_Spinner(color_panel, "Blue:",
                                                      &cur_color_blue_,
                                                      UICtrl::UI_COLOR_B,
                                                      s_gluicallback);
    glui_ctrl_hooks_.spinner_blue->set_float_limits(0, 1.0);

    new GLUI_Button(color_panel, "Red", UICtrl::UI_PRESET_RED,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Orange", UICtrl::UI_PRESET_ORANGE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Yellow", UICtrl::UI_PRESET_YELLOW,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Green", UICtrl::UI_PRESET_GREEN,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Blue", UICtrl::UI_PRESET_BLUE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Purple", UICtrl::UI_PRESET_PURPLE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "White", UICtrl::UI_PRESET_WHITE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Black", UICtrl::UI_PRESET_BLACK,
                    s_gluicallback);
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

void FlashPhotoApp::GluiControl(int control_id) {
  switch (control_id) {
    case UICtrl::UI_PRESET_RED:
      cur_color_red_ = 1;
      cur_color_green_ = 0;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_ORANGE:
      cur_color_red_ = 1;
      cur_color_green_ = 0.5;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_YELLOW:
      cur_color_red_ = 1;
      cur_color_green_ = 1;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_GREEN:
      cur_color_red_ = 0;
      cur_color_green_ = 1;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_BLUE:
      cur_color_red_ = 0;
      cur_color_green_ = 0;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UICtrl::UI_PRESET_PURPLE:
      cur_color_red_ = 0.5;
      cur_color_green_ = 0;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UICtrl::UI_PRESET_WHITE:
      cur_color_red_ = 1;
      cur_color_green_ = 1;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UICtrl::UI_PRESET_BLACK:
      cur_color_red_ = 0;
      cur_color_green_ = 0;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_APPLY_BLUR:
      filter_manager_.ApplyBlur();
      break;
    case UICtrl::UI_APPLY_SHARP:
      filter_manager_.ApplySharpen();
      break;
    case UICtrl::UI_APPLY_MOTION_BLUR:
      filter_manager_.ApplyMotionBlur();
      break;
    case UICtrl::UI_APPLY_EDGE:
      filter_manager_.ApplyEdgeDetect();
      break;
    case UICtrl::UI_APPLY_THRESHOLD:
      filter_manager_.ApplyThreshold(display_buffer_);  // updating new buffer
      break;
    case UICtrl::UI_APPLY_DITHER:
      filter_manager_.ApplyThreshold(display_buffer_);
      break;
    case UICtrl::UI_APPLY_SATURATE:
      filter_manager_.ApplySaturate(display_buffer_);
      break;
    case UICtrl::UI_APPLY_CHANNEL:
      filter_manager_.ApplyChannel(display_buffer_);
      break;
    case UICtrl::UI_APPLY_QUANTIZE:
      filter_manager_.ApplyQuantize(display_buffer_);
      break;
    case UICtrl::UI_APPLY_SPECIAL_FILTER:
      filter_manager_.ApplySpecial();
      break;
    case UICtrl::UI_FILE_BROWSER:
      io_manager_.set_image_file(io_manager_.file_browser()->get_file());
      break;
    case UICtrl::UI_LOAD_CANVAS_BUTTON:
      std::cout << "REDO CLICKED" << std::endl;
      printStack();
      PixelBuffer * nb; // new buffer
      nb = io_manager_.LoadImageToCanvas();
      // Set the window dimensions to the state that was just restored
      SetWindowDimensions(nb->width(), nb->height());
      display_buffer_ = nb;
      // Handle the case which we are not at the end of the undo stack
      maintain_states_stack(cur_state_);
      // Save the new buffer with the image to the undo state
      add_buffer_to_undo_stack(display_buffer_);
      std::cout << "END REDO" << std::endl;
      break;
    case UICtrl::UI_LOAD_STAMP_BUTTON:
      io_manager_.LoadImageToStamp();
      break;
    case UICtrl::UI_SAVE_CANVAS_BUTTON:
      io_manager_.SaveCanvasToFile(display_buffer_, io_manager_.file_name());
      // Reload the current directory:
      io_manager_.file_browser()->fbreaddir(".");
      break;
    case UICtrl::UI_FILE_NAME:
      io_manager_.set_image_file(io_manager_.file_name());
      break;
    case UICtrl::UI_UNDO:
      std::cout << "UNDO CLICKED" << std::endl;
      printStack();
      state_manager_.UndoOperation(display_buffer_, states_, cur_state_);
      cur_state_-= 1; // Decrement the current index after undoing
      printStack();
      // Set the window dimensions to the state that was just restored
      SetWindowDimensions(display_buffer_->width(), display_buffer_->height());
      // Check if the undo button should be disabled (no more states)
      if(cur_state_ > 0) {
        state_manager_.undo_toggle(true);
      }
      else {
        state_manager_.undo_toggle(false);
      }
      // Check if the redo button should be enabled
      if (cur_state_ != states_.size()-1) {
        state_manager_.redo_toggle(true);
      }
      else {
        state_manager_.redo_toggle(false);
      }
      break;
    case UICtrl::UI_REDO:
      std::cout << "REDO CLICKED" << std::endl;
      printStack();
      state_manager_.RedoOperation(display_buffer_, states_, cur_state_);
      cur_state_ += 1;
      SetWindowDimensions(display_buffer_->width(), display_buffer_->height());
      printStack();
      // Check if the redo button should be enabled
      // Handle the case which we are not at the end of the undo stack
      if (cur_state_ != states_.size()-1) {
        state_manager_.redo_toggle(true);
      }
      else {
        state_manager_.redo_toggle(false);
      }
      if(cur_state_ > 0) {
        state_manager_.undo_toggle(true);
      }
      else {
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
void FlashPhotoApp::update_colors(void) {
  glui_ctrl_hooks_.spinner_blue->set_float_val(cur_color_blue_);
  glui_ctrl_hooks_.spinner_green->set_float_val(cur_color_green_);
  glui_ctrl_hooks_.spinner_red->set_float_val(cur_color_red_);
}

void FlashPhotoApp::InitGraphics(void) {
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
/** TODO implement undo queue */
void FlashPhotoApp::add_buffer_to_undo_stack (PixelBuffer* &current_buffer) {
  std::cout << "add_buffer_to_undo_stack" << std::endl;
  printStack();
  PixelBuffer* old_buffer = new PixelBuffer(*current_buffer);
  std::cout << "old_buffer " << old_buffer << std::endl;
  states_.push_back(old_buffer);
  cur_state_ += 1; // Update index
  current_buffer = states_[cur_state_];
  //free(temp_buffer);
  printStack();
  if(cur_state_ > 0) {
    state_manager_.undo_toggle(true);
  }
}

// Handles the case in which we undo and then draw, we need to erase
// any states after this point because they are overwritten
void FlashPhotoApp::maintain_states_stack (int cur_state_) {
  std::cout << "maintain_states_stack" <<  std::endl;
  printStack();
  if (cur_state_ != states_.size()-1) {
    std::cout << "ERASE RAN" << std::endl;
    states_.erase(states_.begin()+cur_state_+1, states_.end());
    state_manager_.redo_toggle(false); // again handle toggle
    printStack();
  }
}

void FlashPhotoApp::printStack() {
  if (states_.size() == 0) {
  }
  else {
    std::cout << "------The Undo Stack-----" << "cur_state_: " << cur_state_ << "  display_buffer_:  " << display_buffer_ << std::endl;
    for(int i = 0; i < states_.size(); i++) {
      std::cout << "|   " << i << "   |   " << states_[i] << "   | " << "Width, Height: " << states_[i]->width() << ", " << states_[i]->height() << std::endl;
    }
  std::cout << "------End of Stack-----" << std::endl;
  }
  
}
}  /* namespace image_tools */
