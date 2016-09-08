//
//  TSprayCan.h
//  Student Support
//
//  Created by Seth Johnson on 2/6/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#ifndef INCLUDE_TSPRAYCAN_H_
#define INCLUDE_TSPRAYCAN_H_

#include "Tool.h"
#include <string>

class TSprayCan : public Tool {
 public:
        TSprayCan();

        std::string getName();
};

#endif  // INCLUDE_TSPRAYCAN_H_
