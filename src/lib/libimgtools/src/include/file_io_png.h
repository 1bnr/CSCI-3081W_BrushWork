/*******************************************************************************
 * Name            : file_io_png.h
 * Project         : FlashPhoto
 * Module          : file_io_png
 * Description     : Header for FileIoPng class
 * Copyright       : Abner Holsinger All rights reserved.
 * Creation Date   : Wed Nov 11 2016
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILE_IO_PNG_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILE_IO_PNG_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <png.h>
#include <string>
#include "file_io.h"
#include "pixel_buffer.h"

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
class FileIoPng : public FileIo {
 public:
  FileIoPng(void);
  virtual ~FileIoPng(void);
  virtual PixelBuffer load_image(std::string file_name);
  virtual void save_image(const PixelBuffer & image,
                         const std::string & file_name);
};
}  /* namespace image_tools */

#endif  /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILE_IO_PNG_H_ */
