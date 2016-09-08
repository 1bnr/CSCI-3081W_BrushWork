//
//  TChalk.h
//  PaintShopTester
//
//  Created by Seth Johnson on 2/26/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#ifndef INCLUDE_TCHALK_H_
#define INCLUDE_TCHALK_H_

#include "Tool.h"
#include <string>

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

#endif  // INCLUDE_TCHALK_H_
