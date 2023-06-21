#pragma once

#include <stdint.h>
#include <stddef.h>
#include <video/framebuffer.hpp>

class Vbe : public Framebuffer {
    private:
        uint32_t* frontBuffer;
    public:
        void init();
        void update();
};

extern Vbe Gfx;