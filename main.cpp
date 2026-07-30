#include "tgaimage.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdlib>le

// compile time constants - do not depent on runtime input or file I/O, dynamic memory allocation, etc.
constexpr TGAColor white = {255, 255, 255, 255};
constexpr TGAColor green = {0, 255, 0, 255};
constexpr TGAColor red = {0, 0, 255, 255};
constexpr TGAColor blue = {255, 128, 64, 255};
constexpr TGAColor yellow = {0, 200, 255, 255};

// draw lines/triangle connecting dots
void line(int aX, int aY, int bX, int bY, TGAImage &buffer, TGAColor color)
{
    float steps = std::max(std::abs(bX - aX), std::abs(bY - aY));
    for (int i = 0; i <= steps; ++i)
    {
        float stepProgress = i / steps;
        int x = std::round(aX + (bX - aX) * stepProgress);
        int y = std::round(aY + (bY - aY) * stepProgress);

        buffer.set(x, y, color);
    }
}

// argument count and vector as params
int main(int argc, char **argv)
{
    constexpr int width = 64;
    constexpr int height = 64;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    // int aX = 7, aY = 3;
    // int bX = 12, bY = 34;
    // int cX = 60, cY = 53;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < (1 << 24); i++)
    {
        const int ax = std::rand() % width;
        const int ay = std::rand() % height;
        const int bx = std::rand() % width;
        const int by = std::rand() % height;
        line(ax, ay, bx, by, framebuffer, {static_cast<std::uint8_t>(std::rand() % 256), static_cast<std::uint8_t>(std::rand() % 256), static_cast<std::uint8_t>(std::rand() % 256), static_cast<std::uint8_t>(std::rand() % 256)});
    }

    // framebuffer.set(aX, aY, white);
    // framebuffer.set(bX, bY, green);
    // framebuffer.set(cX, cY, red);

    framebuffer.write_tga_file("triangle.tga");
}