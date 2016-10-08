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

 //The Draw fucntion, take in a color object and the pointer to our display buffer
void Tool::Draw(int x, int y, PixelBuffer *p, ColorData c) {
	//hard coded in the specs for the pen mask boundries,for testing sake
	// this is where I will be making more changes
	int rows = 3;
	int cols = 3;
	int xpos_start = x - rows/2; //set the start xpos
	int xpos_end = x + rows/2;
	int ypos_start = y - cols/2; 
	int ypos_end = y + cols/2;

	std::cout << "PRINT" << std::endl; 
	//loop through the coordinates that the mask will effect and set the points to the color that we want
	//also note that I'm not yet handling the fall off in the mask, because this is just hard coded in
	for(int i = xpos_start; i <= xpos_end; i++) {
		for(int j = ypos_start; j <= ypos_end; j++) {
			std::cout << "i: " << i << std::endl; 
			std::cout << "j: " << j << std::endl; 
			p->set_pixel(i, j, c);  //set the current pixel to the display buffer that we passed in
		}
	}

}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

}  // namespace image_tools
