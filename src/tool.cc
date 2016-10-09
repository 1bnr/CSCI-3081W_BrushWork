/*******************************************************************************
 * Name            : tool.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Tool class
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 10/05/16
 * Original Author : Isaac Schwab
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/tool.h"
#include <cmath>
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Tool::Tool() {
}

Tool::~Tool() {}

 //The Draw fucntion, take in a color object & the pointer to display buffer
void Tool::Draw(int x, int y, PixelBuffer *p, ColorData c) {
	int t_x_ = x;
	int t_y_ = p->height() - y;
	//hard coded in the specs for the pen mask boundries,for testing sake
	// this is where I will be making more changes
//	int rows = (*mask_size_);
//	int cols = (*mask_size_);
	int xpos_start = t_x_ - mask_rows_/2; //set the start xpos
	int xpos_end = t_x_ + mask_rows_/2;
	int ypos_start = t_y_ - mask_cols_/2; 
	int ypos_end = t_y_ + mask_cols_/2;

  // filter the pixel data from the canvas and the tool through the mask, and apply them to the canvas
  for(int i = 0; i < mask_rows_; i++) {
    for(int j = 0; j < mask_cols_; j++) {
      ColorData canvas_pixel = (p->get_pixel(xpos_start + i, ypos_start + j)) * static_cast<float>(1.0 - tool_mask_[i][j]);
      ColorData tool_pixel = c * (static_cast<float>(tool_mask_[i][j]));
// print out the mask      
//std::cout << tool_mask_[i][j] << ":";

      ColorData new_pixel = canvas_pixel + tool_pixel;     
        //set the current pixel to the display buffer that we passed in
        p->set_pixel(j + xpos_start, i + ypos_start, new_pixel);  

    }
// skip to next line of mask for printout
//std::cout << std::endl;

  }
// space between filter printouts
//std::cout << std::endl;


}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

}  // namespace image_tools
