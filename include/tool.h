/*******************************************************************************
 * Name            : tool.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Tools class.
 * Copyright       : 2016 CSCI3081W Team 0x07 All rights reserved.
 * Creation Date   : 10/05/16
 * Original Author : Isaac Schwab
 *
 ******************************************************************************/

#ifndef INCLUDE_TOOL_H_
#define INCLUDE_TOOL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include "include/base_gfx_app.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"

 /*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This Tool class is the abstract class for the type Tool.
 * Subtypes of Tool will override and implement some of these functions.
 */
class Tool {
 public:
  // Default constructor for a tool.
  Tool();
  virtual ~Tool();
  inline void use_luminance() {uses_luminance_ = true;}
  inline int get_mask_rows() {return mask_rows_;}
  inline int get_mask_cols() {return mask_cols_;}
  inline void set_mask_rows(int rows) {mask_rows_ = rows;}
  inline void set_mask_cols(int cols) {mask_cols_ = cols;}
  inline void set_tool_mask(std::vector<std::vector<float> > mask) {
    tool_mask_ = mask;
  }
  inline std::vector<std::vector<float>> get_tool_mask() {
    return tool_mask_;
  }

  // Discussed possible ways to implement draw function with group
  virtual void Draw(int x, int y, PixelBuffer *p, ColorData c);
 private:
  int mask_rows_;
  int mask_cols_;
  bool uses_luminance_ = false;
  std::vector<std::vector<float>> tool_mask_;
};
}  // namespace image_tools
#endif  // INCLUDE_TOOL_H_
