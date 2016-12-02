/*******************************************************************************
 * Name            : io_file.h
 * Project         : FlashPhoto
 * Module          : io_file
 * Description     : Header for JpgLoader class
 * Copyright       : Abner Holsinger All rights reserved.
 * Creation Date   : Wed Nov 14 2016
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
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
 * @brief parent class for all file io modules; non instantiatable; contains
 * no method definitions. Class has only load_image and save_image full virtual
 * methods that will be defined in all subclasses.
 */
FileIo::FileIo(void) {}
FileIo::~FileIo(void) {}
}  /* namespace image_tools */
