/*******************************************************************************
 * Name            : jpg_loader.h
 * Project         : FlashPhoto
 * Module          : jpg_loader
 * Description     : Header for JpgLoader class
 * Copyright       : Abner Holsinger All rights reserved.
 * Creation Date   : Wed Nov 11 2016
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_JPG_LOADER_H_
#define SRC_INCLUDE_JPG_LOADER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <jpeglib.h>
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
class JpgLoader {
 public:
  JpgLoader(void);
  virtual ~JpgLoader(void);

  PixelBuffer static load_image(std::string file_name);
  void static save_image(const PixelBuffer & image, const std::string & file_name);
};
/* some class global fields */
struct my_error_mgr {
struct jpeg_error_mgr pub; /* "public" fields */
jmp_buf setjmp_buffer; /* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

}  /* namespace image_tools */

#endif  /* SRC_INCLUDE_JPG_LOADER_H_ */
