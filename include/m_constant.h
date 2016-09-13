/*******************************************************************************
 * Name            : m_constant.h
 * Project         : csci3081
 * Module          : Mask
 * Description     : Header File for Constant Mask class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_MCONSTANT_H_
#define INCLUDE_MCONSTANT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "mask.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief MConstant is a Mask that is round, with a constant fill  value.
 */
class MConstant : public Mask {
 public:
  MConstant(float radius, float opacity);

 protected:
  float get_intensity(int x, int y, float radius);
};
}  // namespace image_tools

#endif  // INCLUDE_MCONSTANT_H_
