#pragma once

#include <stdint.h>
#include <stddef.h>
#include <video/framebuffer.hpp>

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
        uint32_t* buffer;

        Framebuffer gc; // Graphics context

        void create(char* name, int w, int h, int x, int y);
        void update();
        void draw();
};