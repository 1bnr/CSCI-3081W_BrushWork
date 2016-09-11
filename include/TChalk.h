/*******************************************************************************
 * Name            : TChalk.h
 * Project         : BrushWork
 * Module          : ??
 * Description     : Header file for Chalk class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_TCHALK_H_
#define INCLUDE_TCHALK_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Tool.h"
#include <string>

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

class TChalk : public Tool {
 public:
        TChalk();

        // overrides super's implementation
        ColorData colorBlendMath(
            float mask,
            ColorData toolColor,
            ColorData canvasColor,
            ColorData backgroundColor);

        std::string getName();

 private:
    unsigned m_rand_seed;
};
}  // namespace csci3081

#endif  // INCLUDE_TCHALK_H_
