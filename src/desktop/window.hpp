#pragma once

#include <stdint.h>
#include <stddef.h>

class Window {
    public:
        char* name;
        int w;
        int h;
        int x;
        int y;
        int offX;
        int offY;
        bool moving;
        int properties;

        Window(char* name, int w, int h, int x, int y);
        void update();
        void draw();
};