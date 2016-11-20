/*******************************************************************************
 * Name            : t_blur.h
 * Project         : image_tools
 * Module          : Tool
 * Description     : Header file for Blur class
 * Copyright       : 2016 Abner Holsinger. All rights reserved.
 * Creation Date   : 11/20/16
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_T_BLUR_H_
#define SRC_INCLUDE_T_BLUR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
#include "include/tool.h"
#include "include/m_linear.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This tool blurs a pixel with the surrounding pixels.
 * It has an linear mask with a radius of 20.0 (diameter of 41).
 */
class TBlur : public Tool {
 public:
  TBlur(void);

  std::string name(void) { return "Blur"; }
  void ApplyToBuffer(int tool_x, int tool_y, ColorData tool_color,
                     PixelBuffer* buffer, PixelBuffer* stamp);
 private:
  int w_width_;
  int w_height_;
  bool is_in_bounds(int x, int y);
  std::vector<ColorData> get_pixels(int x_center, int y_center,
                                    int radius, const PixelBuffer &buffer);
};

}  /* namespace image_tools */

#endif  /* SRC_INCLUDE_T_BLUR_H_ */
