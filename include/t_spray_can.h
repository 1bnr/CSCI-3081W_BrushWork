/*******************************************************************************
 * Name            : t_spray_can.h
 * Project         : csci3081
 * Module          : Tool
 * Description     : Header file for SprayCan tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_T_SPRAY_CAN_H_
#define INCLUDE_T_SPRAY_CAN_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "include/tool.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief SETH FILL THIS IN
 */
class TSprayCan : public Tool {
 public:
  TSprayCan(void);

  std::string name(void) { return "Spray Can"; }
};
}  // namespace image_tools

#endif  // INCLUDE_T_SPRAY_CAN_H_
