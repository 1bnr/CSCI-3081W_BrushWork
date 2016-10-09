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
	
	//the following variables are setup to handle pizels surround the cursor
	int rows = mask_rows_;
	int cols = mask_cols_;
	int xpos_start = t_x_ - rows/2; //set the start xpos
	int xpos_end = t_x_ + rows/2;
	int ypos_start = t_y_ - cols/2; 
	int ypos_end = t_y_ + cols/2;

	//indexes for the current position of the mask array
	int mask_x = 0;
	int mask_y = 0;
	//loop through the coordinates that the mask will effect 
	//and set the points to the color that we want
	for(int i = xpos_start; i <= xpos_end; i++) {
		for(int j = ypos_start; j <= ypos_end; j++) {
			std::cout << "i: " << mask_x << std::endl; 
			std::cout << "j: " << mask_y << std::endl;
			std::cout << "Mask Val: " << tool_mask_[mask_x][mask_y]  << std::endl;
			//don't draw to the buffer if the current mask position is empty
			if(tool_mask_[mask_x][mask_y] > 0) {
				p->set_pixel(i, j, c);  //set the current pixel to the display buffer that we passed in
			}
			mask_y+=1;
		}
		mask_y = 0;
		mask_x+=1;
	}

}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

}  // namespace image_tools
