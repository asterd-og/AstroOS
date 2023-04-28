#include <desktop/window.hpp>
#include <video/framebuffer.hpp>
#include <sys/ps2/mouse.hpp>
#include <lib/math.hpp>
#include <sys/serial.hpp>

Window::Window(char* name, int w, int h, int x, int y) {
    this->name = name;
    this->w = w;
    this->h = h;
    this->x = x;
    this->y = y;
    this->moving = false;
}

void Window::update() {
    if (Mouse::left()) {
        if (Mouse::x() >= this->x && Mouse::x() <= this->x + this->w &&
            Mouse::y() >= this->y - 16 && Mouse::y() <= this->y) {
            if (!this->moving) {
                this->moving = true;
                this->offX = Mouse::x() - this->x;
                this->offY = Mouse::y() - this->y;
            }
        }
    } else {
        if (this->moving) this->moving = false;
    }

    if (this->moving) {
        this->x = clamp(Mouse::x() - this->offX, 0, Gfx.width);
        this->y = clamp(Mouse::y() - this->offY, 16, Gfx.height);
    }
}

void Window::draw() {
    Gfx.drawFillRect(this->x, this->y - 16, this->w, this->h,
                     BLACK);
    Gfx.drawFillRect(this->x + 4, this->y, this->w - 8,
                     this->h - 20, DARKGRAY);
    Gfx.drawString(this->x + 4, this->y - 16, this->name,
                   WHITE, FONT_SLIM_8x16);
}