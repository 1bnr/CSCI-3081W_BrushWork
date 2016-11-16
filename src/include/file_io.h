/*******************************************************************************
 * Name            : file_io.h
 * Project         : FlashPhoto
 * Module          : file_io
 * Description     : Header for JpgLoader class
 * Copyright       : Abner Holsinger All rights reserved.
 * Creation Date   : Wed Nov 14 2016
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_FILE_IO_H_
#define SRC_INCLUDE_FILE_IO_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
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
 * @brief parent class for all file io modules
 */
class FileIo {
 public:
  FileIo(void);
  virtual ~FileIo(void);
  virtual PixelBuffer load_image(std::string file_name) = 0;
  virtual void save_image(const PixelBuffer & image, const std::string & file_name) = 0;
};

}  /* namespace image_tools */

#endif  /* SRC_INCLUDE_FILE_IO_H_ */
