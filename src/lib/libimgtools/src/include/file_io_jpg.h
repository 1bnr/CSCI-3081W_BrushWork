/*******************************************************************************
 * Name            : file_io_jpg.h
 * Project         : FlashPhoto
 * Module          : file_io_jpg
 * Description     : Header for FileIoJpg class
 * Copyright       : Abner Holsinger All rights reserved.
 * Creation Date   : Wed Nov 11 2016
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_FILE_IO_JPG_H_
#define SRC_INCLUDE_FILE_IO_JPG_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <jpeglib.h>
#include <string>
#include "include/file_io.h"
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
class FileIoJpg : public FileIo {
 private:
 public:
  FileIoJpg(void);
  virtual ~FileIoJpg(void);
  virtual PixelBuffer load_image(std::string file_name);
  virtual void save_image(const PixelBuffer & image,
                         const std::string & file_name);
};
/* some class global fields */
struct my_error_mgr {
struct jpeg_error_mgr pub; /* "public" fields */
jmp_buf setjmp_buffer; /* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

}  /* namespace image_tools */

#endif  /* SRC_INCLUDE_FILE_IO_JPG_H_ */
