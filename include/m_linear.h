/*******************************************************************************
 * Name            : m_linear.h
 * Project         : csci3081
 * Module          : Mask
 * Description     : Header file for Linear mask class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_MLINEAR_H_
#define INCLUDE_MLINEAR_H_

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
 * @brief MLinear is a Mask that is round, with a linear fall-off from full
 * intensity at the center to no intensity at the  extremity.
 */
class MLinear : public Mask {
 public:
  MLinear(float radius, float opacity);

 protected:
  float get_intensity(int x, int y, float radius);
};

}  // namespace image_tools

#endif  // INCLUDE_MLINEAR_H_
