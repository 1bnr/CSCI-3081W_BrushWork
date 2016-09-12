/*******************************************************************************
 * Name            : Tool.h
 * Project         : csci3081
 * Module          : ??
 * Description     : Header file for Tool abstract class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_TOOL_H_
#define INCLUDE_TOOL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "PixelBuffer.h"
#include "ColorData.h"
#include "Mask.h"

#include <string>

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * Tool is the representation of a particular PaintShop tool.
 * This baseclass is abstract and does not provide a default mask.
 * Tools inherited from this class should provide a name and a mask.
 * Inherited classes may optionally override the default colorBlendMath.
 **/
class Tool {
public:
    Tool(void);
    virtual ~Tool(void);

    virtual void ApplyToBuffer(
        int toolX,
        int toolY,
        ColorData toolColor,
        PixelBuffer* buffer);
    virtual std::string name(void) = 0;

protected:
    virtual ColorData color_blend_math(
        float mask,
        ColorData toolColor,
        ColorData canvasColor,
        ColorData backgroundColor);
    Mask* mask(void) { return mask_; }
    void mask(Mask* mask) { mask_ = mask; }

private:
    Tool(const Tool& rhs) = delete;
    Tool& operator=(const Tool& rhs) = delete;

    Mask *mask_;
};
}  // namespace csci3081
#endif  // INCLUDE_TOOL_H_
