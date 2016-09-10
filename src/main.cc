//
//  main.cpp
//  Copyright 2016 CSci-3081W TAs.
//


#include "BrushWorkApp.h"
#include "ColorData.h"

int main(int argc, char* argv[]) {
    BrushWorkApp *app = new BrushWorkApp(argc, argv, 800, 800,
                                         ColorData(1,
                                                   1,
                                                   static_cast<float>(0.95)));
    // runMainLoop returns when the user closes the graphics window.
    app->RunMainLoop();
    delete app;
    exit(0);
}
