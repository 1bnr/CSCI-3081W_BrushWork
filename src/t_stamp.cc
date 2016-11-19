/*******************************************************************************
 * Name            : t_stamp.cc
 * Project         : FlashPhoto
 * Module          : Tool
 * Description     : Implementation of chalk tool class
 * Copyright       : 2016 Abner Holsinger. All rights reserved.
 * Creation Date   : 11/18/16
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include <cstdlib>
#include <string>
#include <iostream>
#include "include/flashphoto_app.h"
#include "include/t_stamp.h"
#include "include/file_io.h"
#include "include/m_constant.h"
#include "include/color_data.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
TStamp::TStamp(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void TStamp::ApplyToBuffer(
    int tool_x,
    int tool_y,
    ColorData tool_color,
    PixelBuffer* buffer,
    PixelBuffer* stamp) {
  int s_width = stamp->width();
  int s_height = stamp->height();
  int d_width = buffer->width();
  int d_height = buffer->height();
  int s_xleft = tool_x - (s_width/2);
  int s_ytop = tool_y - (s_height/2);
  int s_xright = s_xleft + s_width;
  int s_ybottom = s_ytop + s_height;

  for (int y=0; y<s_height; y++) {
    /* bounds check the pixel application */
    if (!((s_ytop + y) < 0 || (s_ytop + y) > (d_height -1)) )
    for (int x=0; x<s_width; x++) {
      /* bounds check the pixel application */
      ColorData pxl = stamp->get_pixel(x,y);
      if (pxl.alpha() > 0){
        buffer->set_pixel((s_xleft + x),(s_ytop + y),pxl);
      }
    }
  }


    }
}  /* namespace image_tools */
