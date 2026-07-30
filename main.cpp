#include <cmath>
#include <tuple>
#include "geometry.h"
#include "model.h"
#include "tgaimage.h"
#include <iostream>

constexpr int width = 128;
constexpr int height = 128;

constexpr TGAColor white = {255, 255, 255, 255};
constexpr TGAColor green = {0, 255, 0, 255};
constexpr TGAColor red = {0, 0, 255, 255};
constexpr TGAColor blue = {255, 128, 64, 255};
constexpr TGAColor yellow = {0, 200, 255, 255};

void line(int ax, int ay, int bx, int by, TGAImage &framebuffer, TGAColor color)
{
    bool steep = std::abs(ax - bx) < std::abs(ay - by);
    if (steep)
    {
        std::swap(ax, ay);
        std::swap(bx, by);
    }
    if (ax > bx)
    {
        std::swap(ax, bx);
        std::swap(ay, by);
    }
    int y = ay;
    int ierror = 0;
    for (int x = ax; x <= bx; x++)
    {
        if (steep)
        {
            framebuffer.set(y, x, color);
        }
        else
        {
            framebuffer.set(x, y, color);
        }
        ierror += 2 * std::abs(by - ay);
        if (ierror > bx - ax)
        {
            y += by > ay ? 1 : -1;
            ierror -= 2 * (bx - ax);
        }
    }
}

// sort triangle vertices by y-coordinate ascending (y0 <= y1 <= y2)
void sort_vertices_by_y(int &aX, int &aY, int &bX, int &bY, int &cX, int &cY)
{
    if (aY > bY)
    {
        std::swap(aX, bX);
        std::swap(aY, bY);
    }
    if (aY > cY)
    {
        std::swap(aX, cX);
        std::swap(aY, cY);
    }
    if (bY > cY)
    {
        std::swap(bX, cX);
        std::swap(bY, cY);
    }
}

// fill triangle defined by vertices (ax, ay), (bx, by), (cx, cy) with color
void fill_triange(int aX, int aY, int bX, int bY, int cX, int cY, TGAImage &framebuffer, TGAColor color)
{
    sort_vertices_by_y(aX, aY, bX, bY, cX, cY);

    if (bY == aY)
    {
        for (int y = aY; y <= cY; ++y)
        {
            const int left = std::min(aX, cX);
            const int right = std::max(aX, cX);
            for (int x = left; x <= right; ++x)
            {
                framebuffer.set(x, y, color);
            }
        }
        return;
    }

    for (int y = aY; y <= cY; ++y)
    {
        const float t = (y - aY) / static_cast<float>(cY - aY);
        const int left = std::round(aX + (cX - aX) * t);
        const int right = std::round(bX + (cX - bX) * t);

        for (int x = std::min(left, right); x <= std::max(left, right); ++x)
        {
            framebuffer.set(x, y, color);
        }
    }
}

void triangle(int ax, int ay, int bx, int by, int cx, int cy, TGAImage &framebuffer, TGAColor color)
{

    std::cout << "Sorted verticies:\n";
    std::cout << "A: (" << ax << ", " << ay << ")\n";
    std::cout << "B: (" << bx << ", " << by << ")\n";
    std::cout << "C: (" << cx << ", " << cy << ")\n";

    // line(ax, ay, bx, by, framebuffer, color);
    // line(bx, by, cx, cy, framebuffer, color);
    // line(cx, cy, ax, ay, framebuffer, color);

    fill_triange(ax, ay, bx, by, cx, cy, framebuffer, color);
}

int main(int argc, char **argv)
{
    TGAImage framebuffer(width, height, TGAImage::RGB);
    triangle(7, 45, 35, 100, 45, 60, framebuffer, red);
    triangle(120, 35, 90, 5, 45, 110, framebuffer, white);
    triangle(115, 83, 80, 90, 85, 120, framebuffer, green);
    framebuffer.write_tga_file("filled_triangle.tga");
    return 0;
}