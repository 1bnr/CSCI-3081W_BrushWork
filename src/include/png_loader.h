/*******************************************************************************
 * Name            : png_loader.h
 * Project         : FlashPhoto
 * Module          : png_loader
 * Description     : Header for PngLoader class
 * Copyright       : Abner Holsinger All rights reserved.
 * Creation Date   : Wed Nov 11 2016
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_PNG_LOADER_H_
#define SRC_INCLUDE_PNG_LOADER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <png.h>
#include <string>
#include "include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief handles loading an image from a file to the stamp.
 */
class PngLoader {
 public:
  PngLoader(void);
  virtual ~PngLoader(void);

  PixelBuffer static load_image(std::string file_name);
};
}  /* namespace image_tools */

#endif  /* SRC_INCLUDE_PNG_LOADER_H_ */
