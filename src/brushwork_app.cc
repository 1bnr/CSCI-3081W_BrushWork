/*******************************************************************************
 * Name            : brushwork_app.cc
 * Project         : BrushWork
 * Module          : App
 * Description     : Implementation of BrushWrok
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/brushwork_app.h"
#include <cmath>
#include <iostream>
#include <vector>
#include "include/color_data.h"
#include "include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
BrushWorkApp::BrushWorkApp(int width,
                           int height)
    : BaseGfxApp(width,
                 height),
      display_buffer_(nullptr),
      cur_tool_(0.0),
      cur_color_red_(0.0),
      cur_color_green_(0.0),
      cur_color_blue_(0.0),
      spinner_r_(nullptr),
      spinner_g_(nullptr),
      spinner_b_(nullptr),
      start_x_(0),
      start_y_(0),
      background_color_( new ColorData(0, 0, 0, 0)),
      cur_color_( new ColorData(0, 0, 0, 0)) {}

BrushWorkApp::~BrushWorkApp(void) {
    if (display_buffer_) {
      delete display_buffer_;
    }
    if (cur_color_) {
      delete cur_color_;
    }
    if (background_color_) {
      delete background_color_;
    }
    tool_list_.clear();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void BrushWorkApp::Init(
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
    set_caption("BrushWork");

    // Initialize Interface
    InitializeBuffers(background_color, width(), height());

    InitGlui();
    InitGraphics();
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    // Create list of tools
    InitTools();
    ColorData *temp_bc = new ColorData(background_color);
    delete background_color_;
    background_color_ = temp_bc;
    ColorData *temp_cc = new ColorData(background_color);
    delete cur_color_;
    cur_color_ = temp_cc;
}

void BrushWorkApp::Display(void) {
    switch (cur_tool_) {
      case 1:  // eraser
              cur_color_->red(background_color_->red());
              cur_color_->green(background_color_->green());
              cur_color_->blue(background_color_->blue());
              cur_color_->alpha(background_color_->alpha());
              glutSetCursor(GLUT_CURSOR_DESTROY);
              break;
      case 2:  // spray can
              cur_color_->red(cur_color_red_);
              cur_color_->green(cur_color_green_);
              cur_color_->blue(cur_color_blue_);
              glutSetCursor(GLUT_CURSOR_SPRAY);
              break;
      case 5:  // blur
              cur_color_->red(cur_color_red_);
              cur_color_->green(cur_color_green_);
              cur_color_->blue(cur_color_blue_);
              glutSetCursor(GLUT_CURSOR_INFO);
              break;
      case 3:  // calligraphy pen
      case 4:  // highlighter
      case 0:  // pen
              cur_color_->red(cur_color_red_);
              cur_color_->green(cur_color_green_);
              cur_color_->blue(cur_color_blue_);
              glutSetCursor(GLUT_CURSOR_CROSSHAIR);
              break;
    }
    DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

void BrushWorkApp::MouseDragged(int x, int y) {
    // Check for out of bound conditions
    x = CheckXBounds(x);
    y = CheckYBounds(y);
    float third_tool_width = tool_list_[cur_tool_]->get_mask_cols()/3;
    float x_increment;
    float y_increment;
    // find the distance between the last xy-coord and this xy-coord
    int x_dif = std::abs(BrushWorkApp::start_x_ - x);
    int y_dif = std::abs(BrushWorkApp::start_y_ - y);
    int stepping_limit;  // the greater of x_dif or y_dif
    // set stepping limit
    if (x_dif > y_dif)
        stepping_limit = x_dif;
    else
        stepping_limit = y_dif;
    // set stepping intervals by dividing distance by the number of steps needed
    x_increment = static_cast<float>(BrushWorkApp::start_x_ - x) /
                                      stepping_limit;
    y_increment = static_cast<float>(BrushWorkApp::start_y_ - y) /
                                      stepping_limit;
    // step from last xy-coord to current xy-coord
    for (int i = 0; i < stepping_limit; i += third_tool_width) {
      tool_list_[cur_tool_]->Draw(x + static_cast<int>(round(i * x_increment)),
                                y + static_cast<int>(round(i * y_increment)),
                                display_buffer_, *cur_color_);
    }
    BrushWorkApp::start_x_ = x;
          BrushWorkApp::start_y_ = y;
//    std::cout << "mouseDragged " << x << " " << y << std::endl;
}
void BrushWorkApp::MouseMoved(int x, int y) {}

void BrushWorkApp::LeftMouseDown(int x, int y) {
    BrushWorkApp::start_x_ = x;
    BrushWorkApp::start_y_ = y;
//    std::cout << "mousePressed" << x << " " << y << std::endl;
    tool_list_[cur_tool_]->Draw(x, y, display_buffer_, *cur_color_);
}

void BrushWorkApp::LeftMouseUp(int x, int y) {
//    std::cout << "mouseReleased " << x << " " << y << std::endl;
}

// Initialize the array of tools
void BrushWorkApp::InitTools(void) {
    Tool *pen = new Pen();
    Tool *eraser = new Eraser();
    Tool *spray_can = new SprayCan();
    Tool *cali_pen = new CalligraphyPen();
    Tool *highlighter = new Highlighter();
    Tool *blur = new Blur();
    tool_list_.push_back(pen);
    tool_list_.push_back(eraser);
    tool_list_.push_back(spray_can);
    tool_list_.push_back(cali_pen);
    tool_list_.push_back(highlighter);
    tool_list_.push_back(blur);
}

void BrushWorkApp::InitializeBuffers(
    ColorData background_color,
    int width,
    int height) {
    display_buffer_ = new PixelBuffer(width, height, background_color);
}

int BrushWorkApp::CheckXBounds(int x) {
    if (x > width())
      return width();
    else if (x < 0)
      return 0;
    else
      return x;
}

int BrushWorkApp::CheckYBounds(int y) {
    if (y > height())
      return height();
    else if (y < 0)
      return 0;
    else
      return y;
}

void BrushWorkApp::InitGlui(void) {
    // Select first tool (this activates the first radio button in glui)
    cur_tool_ = 0;

    GLUI_Panel *tool_panel = new GLUI_Panel(glui(), "Tool Type");
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(tool_panel,
                                                 &cur_tool_,
                                                 UI_TOOLTYPE,
                                                 s_gluicallback);

    // Create interface buttons for different tools:
    new GLUI_RadioButton(radio, "Pen");
    new GLUI_RadioButton(radio, "Eraser");
    new GLUI_RadioButton(radio, "Spray Can");
    new GLUI_RadioButton(radio, "Caligraphy Pen");
    new GLUI_RadioButton(radio, "Highlighter");
    new GLUI_RadioButton(radio, "Blur tool");

    GLUI_Panel *color_panel = new GLUI_Panel(glui(), "Tool Color");

    cur_color_red_ = 0;
    spinner_r_  = new GLUI_Spinner(color_panel, "Red:", &cur_color_red_,
                                   UI_COLOR_R, s_gluicallback);
    spinner_r_->set_float_limits(0, 1.0);

    cur_color_green_ = 0;
    spinner_g_ = new GLUI_Spinner(color_panel, "Green:", &cur_color_green_,
                                   UI_COLOR_G, s_gluicallback);
    spinner_g_->set_float_limits(0, 1.0);

    cur_color_blue_ = 0;
    spinner_b_  = new GLUI_Spinner(color_panel, "Blue:", &cur_color_blue_,
                                   UI_COLOR_B, s_gluicallback);
    spinner_b_->set_float_limits(0, 1.0);
    new GLUI_Button(color_panel, "Red", UI_PRESET_RED, s_gluicallback);
    new GLUI_Button(color_panel, "Orange", UI_PRESET_ORANGE, s_gluicallback);
    new GLUI_Button(color_panel, "Yellow", UI_PRESET_YELLOW, s_gluicallback);
    new GLUI_Button(color_panel, "Green", UI_PRESET_GREEN, s_gluicallback);
    new GLUI_Button(color_panel, "Blue", UI_PRESET_BLUE, s_gluicallback);
    new GLUI_Button(color_panel, "Purple", UI_PRESET_PURPLE, s_gluicallback);
    new GLUI_Button(color_panel, "White", UI_PRESET_WHITE, s_gluicallback);
    new GLUI_Button(color_panel, "Black", UI_PRESET_BLACK, s_gluicallback);


    new GLUI_Button(glui(), "Quit", UI_QUIT, static_cast<GLUI_Update_CB>(exit));
}


void BrushWorkApp::InitGraphics(void) {
    // Initialize OpenGL for 2D graphics as used in the BrushWork app
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

void BrushWorkApp::GluiControl(int control_id) {
    switch (control_id) {
    case UI_PRESET_RED:
        cur_color_red_ = 1;
        cur_color_green_ = 0;
        cur_color_blue_ = 0;
        break;
    case UI_PRESET_ORANGE:
        cur_color_red_ = 1;
        cur_color_green_ = 0.5;
        cur_color_blue_ = 0;
        break;
    case UI_PRESET_YELLOW:
        cur_color_red_ = 1;
        cur_color_green_ = 1;
        cur_color_blue_ = 0;
        break;
    case UI_PRESET_GREEN:
        cur_color_red_ = 0;
        cur_color_green_ = 1;
        cur_color_blue_ = 0;
        break;
    case UI_PRESET_BLUE:
        cur_color_red_ = 0;
        cur_color_green_ = 0;
        cur_color_blue_ = 1;
        break;
    case UI_PRESET_PURPLE:
        cur_color_red_ = 0.5;
        cur_color_green_ = 0;
        cur_color_blue_ = 1;
        break;
    case UI_PRESET_WHITE:
        cur_color_red_ = 1;
        cur_color_green_ = 1;
        cur_color_blue_ = 1;
        break;
    case UI_PRESET_BLACK:
        cur_color_red_ = 0;
        cur_color_green_ = 0;
        cur_color_blue_ = 0;
        break;
    default:
        break;
    }

    spinner_b_->set_float_val(cur_color_blue_);
    spinner_g_->set_float_val(cur_color_green_);
    spinner_r_->set_float_val(cur_color_red_);
}
}  // namespace image_tools
