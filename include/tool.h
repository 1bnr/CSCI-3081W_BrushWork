/*******************************************************************************
 * Name            : tool.h
 * Project         : csci3081
 * Module          : Tool
 * Description     : Header file for Tool base class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_TOOL_H_
#define INCLUDE_TOOL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "pixel_buffer.h"
#include "color_data.h"
#include "mask.h"

#include <string>

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Tool is the representation of a particular BrushWork tool.
 * This baseclass is abstract and does not provide a default mask.
 * Tools inherited from this class MUST:\n
 * (1) Provide a name\n
 * (2) Define the mask. You will get an assert error if you do not.\n
 * Inherited classes may optionally override the default color_blend_math().
 */
class Tool {
 public:
  Tool(void);
  virtual ~Tool(void);

  /**
   * @brief Apply the selected tool to the buffer
   * @param[in] toolX The X coordinate of current tool location
   * @param[in] toolY The Y coordinate of current tool location
   * @param[in] toolColor The current color of the tool
   * @param buffer The buffer of pixels to apply the tool to
   */
  virtual void ApplyToBuffer(
    int toolX,
    int toolY,
    ColorData toolColor,
    PixelBuffer* buffer);

  /**
   * @brief The name of the tool
   * @return
   */
  virtual std::string name(void) = 0;

 protected:

  /**
   * @brief The definition of how the tool will operate on a single pixel on
   * the canvas when applied
   * @param[in] mask_pixel_amount Value of the relevant pixal in the mask
   * @param[in] toolColor Current color of the tool
   * @param[in] canvasColor Color of the background if no tool had been applied
   * @param[in] currentColor Color present that this blend would replace
   * @return The new color definition for the pixel
   */
  virtual ColorData color_blend_math(
    float mask_pixel_amount,
    ColorData tool_color,
    ColorData current_color,
    ColorData background_color);

  /**
   * @brief Get the mask associated with the tool
   * @return The mask
   */
  Mask* mask(void) { return mask_; }

  /**
   * Set the mask associated with the tool
   */
  void mask(Mask* mask) { mask_ = mask; }

 private:

  /* Usage of copy/move construction or assignment is disallowed */
  Tool(const Tool& rhs) = delete;
  Tool& operator=(const Tool& rhs) = delete;

  Mask *mask_;
};
}  // namespace image_tools
#endif  // INCLUDE_TOOL_H_
