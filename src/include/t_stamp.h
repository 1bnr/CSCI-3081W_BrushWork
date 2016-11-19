/*******************************************************************************
 * Name            : t_stamp.h
 * Project         : image_tools
 * Module          : Tool
 * Description     : Header file for stamp tool class
 * Copyright       : 2016 Abner Holsinger All rights reserved.
 * Creation Date   : 11/18/16
 * Original Author : Abner Holsinger
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_T_STAMP_H_
#define SRC_INCLUDE_T_STAMP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "include/tool.h"
#include "include/m_constant.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This tool simulates the usage of a stamp.
 */
class TStamp : public Tool {
 public:
  TStamp(void);

  std::string name(void) { return "Stamp"; }
  void ApplyToBuffer(
      int tool_x,
      int tool_y,
      ColorData tool_color,
      PixelBuffer* buffer,
      PixelBuffer* stamp);  
};

}  /* namespace image_tools */

#endif  /* SRC_INCLUDE_T_STAMP_H_ */
