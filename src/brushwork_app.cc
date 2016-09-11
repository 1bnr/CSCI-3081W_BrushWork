/*******************************************************************************
 * Name            : brushwork_app.cc
 * Project         : BrushWork
 * Module          : ??
 * Description     : Implementation of BrushWrok
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "BrushWorkApp.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "Tool.h"
#include "ToolFactory.h"

#include <cmath>
#include <iostream>

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
using std::cout;
using std::endl;
namespace brushwork = csci3081::brushwork;

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
brushwork::BrushWorkApp::BrushWorkApp(int width,
                           int height)
    : BaseGfxApp(width,
                 height),
      display_buffer_(nullptr),
      cur_tool_(0.0),
      tools_(new Tool*[ToolFactory::getNumTools()]),
      cur_color_red_(0.0),
      cur_color_green_(0.0),
      cur_color_blue_(0.0),
      spinner_r_(nullptr),
      spinner_g_(nullptr),
      spinner_b_(nullptr) {}

brushwork::BrushWorkApp::~BrushWorkApp(void) {
    if (display_buffer_) {
        delete display_buffer_;
    }
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void brushwork::BrushWorkApp::Init(
    int argc,
    char* argv[],
    int x,
    int y,
    ColorData backgroundColor) {

    BaseGfxApp::Init(argc,argv,
                     x,y,
                     GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH,
                     true,
                     width()+51,
                     50);

    // Set the name of the window
    set_caption("BrushWork");

    // Initialize Interface
    InitializeBuffers(backgroundColor, width(), height());

    // Create array of tools and populate
    for (int i = 0; i < ToolFactory::getNumTools(); i++) {
        tools_[i] = ToolFactory::createTool(i);
    }
    InitGlui();
    InitGraphics();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
brushwork::BrushWorkApp::~BrushWorkApp(void) {
    // Delete each of the tools before deleting the list of tool pointers.
        if (tools_) {
                Tool ** toolsEnd =  tools_ + ToolFactory::getNumTools();
                for (Tool ** tool_i = tools_; tool_i < toolsEnd; tool_i++) {
                        Tool* tool = *tool_i;
                        if (tool) {
                                delete tool;
                            }
                    }

                delete [] tools_;}
        if (display_buffer_) {
            delete display_buffer_;
        }
}

void brushwork::BrushWorkApp::Display(void) {
    DrawPixels(0, 0, width(), height(), display_buffer_->get_data());
}

void brushwork::BrushWorkApp::mouseDragged(int x, int y) {
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
    float pixelsBetween = fmax(abs(delta_x), abs(delta_y));
    int step_size = 1;

    // Optimize by maxing out at the max_steps,
    // and fill evenly between
    if (pixelsBetween > max_steps) {
        step_size = pixelsBetween/max_steps;
    }

    // Iterate between the event locations
    for (int i = 0; i < pixelsBetween; i+=step_size) {
        int x = mouse_last_x_+(i*delta_x/pixelsBetween);
        int y = mouse_last_y_+(i*delta_y/pixelsBetween);

        tools_[cur_tool_]->applyToBuffer(x, height()-y,
                                         ColorData(cur_color_red_,
                                                   cur_color_green_,
                                                   cur_color_blue_),
                                         display_buffer_);
    }

    // let the previous point catch up with the current.
    mouse_last_x_ = x;
    mouse_last_y_ = y;
}
void brushwork::BrushWorkApp::leftMouseDown(int x, int y) {
    tools_[cur_tool_]>applyToBuffer(x, height()y,
                                    ColorData(cur_color_red_,
                                              cur_color_green_,
                                              cur_color_blue_),
                                    display_buffer_);
}

void brushwork::BrushWorkApp::LeftMouseUp(int x, int y) {
    std::cout << "mouseReleased " << x << " " << y << std::endl;
}

void brushwork::BrushWorkApp::InitializeBuffers(
    ColorData backgroundColor,
    int width,
    int height) {
    display_buffer_ = new PixelBuffer(width, height, backgroundColor);
}

void brushwork::BrushWorkApp::InitGlui(void) {
    // Select first tool (this activates the first radio button in glui)
    cur_tool_ = 0;

    GLUI_Panel *toolPanel = new GLUI_Panel(glui(), "Tool Type");
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel,
                                                 &cur_tool_,
                                                 UI_TOOLTYPE,
                                                 s_gluicallback);

    // Create interface buttons for different tools:
    new GLUI_RadioButton(radio, "Pen");
    new GLUI_RadioButton(radio, "Eraser");
    new GLUI_RadioButton(radio, "Spray Can");
    new GLUI_RadioButton(radio, "Caligraphy Pen");
    new GLUI_RadioButton(radio, "Highlighter");

    GLUI_Panel *colPanel = new GLUI_Panel(glui(), "Tool Color");

    cur_color_red_ = 0;
    spinner_r_  = new GLUI_Spinner(colPanel, "Red:", &cur_color_red_,
                                   UI_COLOR_R, s_gluicallback);
    spinner_r_->set_float_limits(0, 1.0);

    cur_color_green_ = 0;
    spinner_g_ = new GLUI_Spinner(colPanel, "Green:", &cur_color_green_,
                                   UI_COLOR_G, s_gluicallback);
    spinner_g_->set_float_limits(0, 1.0);

    cur_color_blue_ = 0;
    spinner_b_  = new GLUI_Spinner(colPanel, "Blue:", &cur_color_blue_,
                                   UI_COLOR_B, s_gluicallback);
    spinner_b_->set_float_limits(0, 1.0);
    new GLUI_Button(colPanel, "Red", UI_PRESET_RED, s_gluicallback);
    new GLUI_Button(colPanel, "Orange", UI_PRESET_ORANGE, s_gluicallback);
    new GLUI_Button(colPanel, "Yellow", UI_PRESET_YELLOW, s_gluicallback);
    new GLUI_Button(colPanel, "Green", UI_PRESET_GREEN, s_gluicallback);
    new GLUI_Button(colPanel, "Blue", UI_PRESET_BLUE, s_gluicallback);
    new GLUI_Button(colPanel, "Purple", UI_PRESET_PURPLE, s_gluicallback);
    new GLUI_Button(colPanel, "White", UI_PRESET_WHITE, s_gluicallback);
    new GLUI_Button(colPanel, "Black", UI_PRESET_BLACK, s_gluicallback);


    new GLUI_Button(glui(), "Quit", UI_QUIT, static_cast<GLUI_Update_CB>(exit));
}


void brushwork::BrushWorkApp::InitGraphics(void) {
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

void brushwork::BrushWorkApp::GluiControl(int controlID) {
    switch (controlID) {
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
