#include <desktop/window.hpp>
#include <video/vbe.hpp>
#include <sys/ps2/mouse.hpp>
#include <lib/math.hpp>
#include <sys/serial.hpp>
#include <lib/string.hpp>
#include <memory/heap.hpp>

void Window::create(char* name, int w, int h, int x, int y) {
    this->name = name;
    this->w = roundTo(w, 8);
    this->h = roundTo(h, 8);
    this->x = roundTo(x, 8);
    this->y = roundTo(y, 8);
    this->moving = false;
    this->buffer = (uint32_t*)Heap::alloc(this->w * this->h * 4);
    this->gc.create(this->w, this->h, Gfx.getBpp(), Gfx.getPitch(), this->buffer);
}

void Window::update() {
    if (Mouse::left()) {
        if (Mouse::x() >= this->x && Mouse::x() <= this->x + this->w &&
            Mouse::y() >= this->y - 8 && Mouse::y() <= this->y) {
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
        this->x = roundTo(clamp(Mouse::x() - this->offX, 0 , Gfx.width), 8);
        this->y = roundTo(clamp(Mouse::y() - this->offY, 8, Gfx.height), 8);
        // this->x = (clamp(Mouse::x() - this->offX, 0 , Gfx.width) / 8) * 8;
        // this->y = (clamp(Mouse::y() - this->offY, 8, Gfx.height) / 8) * 8;
    }
}

void Window::draw() {
    // Top Bar
    Gfx.drawChar(this->x - 8, this->y - 8, '+', white);
    Gfx.drawChar(this->x, this->y - 8, '-', white);

    Gfx.drawString(this->x + 8, this->y - 8, this->name, white);
    
    for (int i = (8 + (strlen(this->name) * 8)); i < this->w; i += 8)
        Gfx.drawChar(this->x + i, this->y - 8, '-', white);
    
    Gfx.drawChar(this->x + this->w, this->y - 8, '+', white);
    
    // Left Side Bar
    for (int i = 0; i < this->h; i += 8)
        Gfx.drawChar(this->x - 8, this->y + i, '|', white);
    
    // Right Side Bar
    for (int i = 0; i < this->h; i += 8)
        Gfx.drawChar(this->x + this->w, this->y + i, '|', white);
    
    // Bottom Bar
    Gfx.drawChar(this->x - 8, this->y + this->h, '+', white);
    for (int i = 0; i < this->w; i += 8)
        Gfx.drawChar(this->x + i, this->y + this->h, '-', white);
    Gfx.drawChar(this->x + this->w, this->y + this->h, '+', white);

    for (int i = 0; i < this->h; i++)
        for (int j = 0; j < this->w; j++)
            Gfx.drawPixel(j + this->x, i + this->y, this->gc.backBuffer[i * this->w + j]);

    //Gfx.drawGc(this->x, this->y, this->gc);
}