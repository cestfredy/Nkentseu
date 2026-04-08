#include "TestCommon.h"

NkImage img(kImageWidth, kImageHeight);

std::mt19937 rng(42);
std::uniform_real_distribution<double> dist(-10.0, 10.0);

std::vector<Vec4d> cube = {
    {-0.5, -0.5, -0.5, 1}, {0.5, -0.5, -0.5, 1},
    {0.5, 0.5, -0.5, 1}, {-0.5, 0.5, -0.5, 1},
    {-0.5, -0.5, 0.5, 1}, {0.5, -0.5, 0.5, 1},
    {0.5, 0.5, 0.5, 1}, {-0.5, 0.5, 0.5, 1},
};

std::vector<Vec2d> edges = {
    {0, 1}, {1, 2}, {2, 3}, {3, 0},
    {4, 5}, {5, 6}, {6, 7}, {7, 4},
    {0, 4}, {1, 5}, {2, 6}, {3, 7},
};

Vec3d eye{0, 1, 3};
Vec3d target{0, 0, 0};
Vec3d up{0, 1, 0};
Mat4d V = LookAt(eye, target, up);
Mat4d P = Perspective(60.0, double(kImageWidth) / kImageHeight, 0.1, 100.0);
