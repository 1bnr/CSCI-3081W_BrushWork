/*******************************************************************************
 * Name            : tool.cc
 * Project         : BrushWork
 * Module          : ??
 * Description     : Implementation of Tool base class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Tool.h"
#include "ColorData.h"
#include "Mask.h"
#include "PixelBuffer.h"

#include <assert.h>
#include <cmath>
#include <algorithm>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Tool::Tool(void) : mask_(nullptr) {}

Tool::~Tool(void) {
  delete mask_;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ColorData Tool::color_blend_math(float mask,
                               ColorData toolColor,
                               ColorData canvasColor,
                               ColorData backgroundColor) {
  return toolColor*mask + canvasColor*(1.0-mask);
}

void Tool::ApplyToBuffer(int toolX,
                         int toolY,
                         ColorData toolColor,
                         PixelBuffer* buffer) {
  assert(mask_);

  int left_bound = std::max(toolX-mask_->width()/2, 0);
  int right_bound = std::min(toolX+mask_->width()/2,
                             buffer->width()-1);
  int lower_bound = std::max(toolY-mask_->height()/2, 0);
  int upper_bound = std::min(toolY+mask_->height()/2,
                             buffer->height()-1);

  for (int y = lower_bound; y <= upper_bound; y++) {
    for (int x = left_bound; x <= right_bound; x++) {
      int mask_x = x - (toolX-mask_->width()/2);
      int mask_y = y - (toolY-mask_->height()/2);
      float mask_value = mask_->value(mask_x, mask_y);
      ColorData current = buffer->get_pixel(x, y);

      // Because we interpolate the pixels, colors overlap
      // and increase intensity quickly. We found that cubing
      // the mask intensity compensated for this.
      float slimmed_mask_value = powf(mask_value, 3);

      ColorData c = color_blend_math(slimmed_mask_value,
                                   toolColor,
                                   current,
                                   buffer->get_background_color());

      buffer->set_pixel(x, y, c);
    }
  }
}

}  // namespace csci3081
