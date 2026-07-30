#include "tgaimage.h"

// compile time constants - do not depent on runtime input or file I/O, dynamic memory allocation, etc.
constexpr TGAColor white = {255, 255, 255, 255};
constexpr TGAColor green = {0, 255, 0, 255};
constexpr TGAColor red = {0, 0, 255, 255};
constexpr TGAColor blue = {255, 128, 64, 255};
constexpr TGAColor yellow = {0, 200, 255, 255};

// draw lines/triangle connecting dots
void line(int aX, int aY, int bX, int bY, TGAImage &buffer, TGAColor color)
{
    for (float i = 0; i < 1.0f; i += 0.001f)
    {
        int x = std::round(aX + (bX - aX) * i);
        int y = std::round(aY + (bY - aY) * i);

        buffer.set(x, y, color);
    }
}

// argument count and vector as params
int main(int argc, char **argv)
{
    constexpr int width = 64;
    constexpr int height = 64;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    int aX = 7, aY = 3;
    int bX = 12, bY = 34;
    int cX = 60, cY = 53;

    line(aX, aY, bX, bY, framebuffer, blue);
    line(bX, bY, cX, cY, framebuffer, green);
    line(cX, cY, aX, aY, framebuffer, yellow);

    framebuffer.set(aX, aY, white);
    framebuffer.set(bX, bY, green);
    framebuffer.set(cX, cY, red);

    framebuffer.write_tga_file("triangle.tga");
}