/*******************************************************************************
 * Name            : mia_filter_manager.h
 * Project         : MIA
 * Module          : filter_manager
 * Description     : Header for MIAFilterManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 18:40:20 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

#ifndef SRC_APP_MIA_SRC_MIA_FILTER_MANAGER_H_
#define SRC_APP_MIA_SRC_MIA_FILTER_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "../../../lib/libimgtools/src/include/filter_manager.h"
#include "GL/glui.h"
#include "../../../lib/libimgtools/src/include/pixel_buffer.h"
#include "../../../lib/libimgtools/src/include/ui_ctrl.h"
#include "../../../lib/libimgtools/src/include/threshold.h"
#include "../../../lib/libimgtools/src/include/saturate.h"
#include "../../../lib/libimgtools/src/include/quantize.h"
#include "../../../lib/libimgtools/src/include/edge_detect.h"
#include "../../../lib/libimgtools/src/include/blur.h"
#include "../../../lib/libimgtools/src/include/sharpen.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Manager for all aspects of filters in FlashPhoto, including
 * initialization of GLUI control elements for filters, filter creation,
 * application, deletion.
 */
class MIAFilterManager : public FilterManager {
 public:
  MIAFilterManager();

  /**
   * @brief Apply a channel filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyGrayscale(PixelBuffer* p);

  void InitGlui(const GLUI *const glui,
                       void (*s_gluicallback)(int));
};

}  /* namespace image_tools */

#endif  /* SRC_APP_MIA_SRC_MIA_FILTER_MANAGER_H_ */
