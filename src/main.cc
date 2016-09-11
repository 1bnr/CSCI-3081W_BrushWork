/*******************************************************************************
 * Name            : main.cc
 * Project         : BrushWork
 * Module          : ??
 * Description     : Do ALL THE THINGS!
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#include "BrushWorkApp.h"
#include "ColorData.h"

namespace brushwork = csci3081::brushwork;
int main(int argc, char* argv[]) {
  brushwork::BrushWorkApp *app = new brushwork::BrushWorkApp(800,800);
  app->Init(argc, argv,
            50,
            50,
            csci3081::ColorData(1,
                                1,
                                static_cast<float>(0.95)));
  // runMainLoop returns when the user closes the graphics window.
  app->RunMainLoop();
  delete app;
  exit(0);
}
