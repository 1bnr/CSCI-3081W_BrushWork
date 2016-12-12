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

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILE_IO_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILE_IO_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "pixel_buffer.h"

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
  /**
   * @brief load the image specifed into a PixelBuffer.
   * @param file_name a string containing the path and name of the file to open
   * @return on success a PixelBuffer representation of the image, otherwise an
   * empty, 0 x 0 PixelBuffer
   */
  virtual PixelBuffer load_image(std::string file_name) = 0;
  /**
   * @brief save an image to the path specified by the file_name string
   * @param image the PixelBuffer pointer that will point to the loaded image
   * @param file_name a string containing the path and name of the ouput file
   * @return 0 on success, otherwise 1
   * */
  virtual int save_image(const PixelBuffer & image,
                          const std::string & file_name) = 0;
};

}  /* namespace image_tools */

#endif  /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILE_IO_H_ */
