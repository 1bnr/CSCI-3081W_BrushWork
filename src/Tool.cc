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
#include <cmath>
#include <algorithm>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Tool::Tool(void) : m_mask(nullptr) {}

Tool::~Tool(void) {
  delete m_mask;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ColorData Tool::colorBlendMath(float mask,
                               ColorData toolColor,
                               ColorData canvasColor,
                               ColorData backgroundColor) {
  return toolColor*mask + canvasColor*(1.0-mask);
}

void Tool::applyToBuffer(int toolX,
                         int toolY,
                         ColorData toolColor,
                         PixelBuffer* buffer) {
  if (m_mask == nullptr) {
    return;
  }

  int left_bound = std::max(toolX-m_mask->width()/2, 0);
  int right_bound = std::min(toolX+m_mask->width()/2,
                             buffer->width()-1);
  int lower_bound = std::max(toolY-m_mask->height()/2, 0);
  int upper_bound = std::min(toolY+m_mask->height()/2,
                             buffer->height()-1);

  for (int y = lower_bound; y <= upper_bound; y++) {
    for (int x = left_bound; x <= right_bound; x++) {
      int mask_x = x - (toolX-m_mask->width()/2);
      int mask_y = y - (toolY-m_mask->height()/2);
      float mask_value = m_mask->value(mask_x, mask_y);
      ColorData current = buffer->get_pixel(x, y);

      // Because we interpolate the pixels, colors overlap
      // and increase intensity quickly. We found that cubing
      // the mask intensity compensated for this.
      float slimmed_mask_value = powf(mask_value, 3);

      ColorData c = colorBlendMath(slimmed_mask_value,
                                   toolColor,
                                   current,
                                   buffer->get_background_color());

      buffer->set_pixel(x, y, c);
    }
  }
}

}  // namespace csci3081
