/*******************************************************************************
 * Name            : PixelBuffer.h
 * Project         : BrushWork
 * Module          : ??
 * Description     : Header file for PixelBuffer class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_PIXELBUFFER_H_
#define INCLUDE_PIXELBUFFER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "ColorData.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Stores an array of ColorData, such as an image that can be drawn to
 * the screen.
 */
class PixelBuffer {
 public:
  PixelBuffer(int w, int h, ColorData background_color);
  virtual ~PixelBuffer(void);

  /**
   * @brief Set the value for a pixel within the buffer/on the screen
   */
  void set_pixel(int x, int y, const ColorData& color);

  inline ColorData const *data(void) const { return pixels_; }
  inline int height(void) const { return height_; }
  inline int width(void) const { return width_; }

  /**
   * @brief Get the background color that was used to initialize the PixelBuffer
   * @return The background color
   */
  ColorData background_color(void) { return *background_color_; }

  /**
   * @brief Fill the pixel buffer with the specified color
   */
  void FillPixelBufferWithColor(ColorData color);

  /**
   * @brief Get the color of a specific pixel
   * @return The color associated with a specific pixel
   */
  ColorData get_pixel(int x, int y) const;


 private:
  const int width_; /** X dimension--cannot be changed  */
  const int height_; /** Y dimension--cannot be changed  */

  ColorData *pixels_; /** Raw pixel data */
  ColorData *background_color_; /** Color used to initialize the pixel buffer  */

  PixelBuffer(const PixelBuffer&rhs) = delete;
  PixelBuffer& operator=(const PixelBuffer &rhs);
};
}  // namespace csci3081
#endif  // INCLUDE_PIXELBUFFER_H_
