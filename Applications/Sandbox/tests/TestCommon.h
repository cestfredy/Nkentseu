#pragma once

#include <Unitest/Unitest.h>
#include <Unitest/TestMacro.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

#include "NKLogger/NkLog.h"
#include "NKMath/NKMath.h"
#include "Mat4d.h"
#include "NKImage.h"
#include "Quat.h"

using namespace NkMath;

inline constexpr int kImageWidth = 512;
inline constexpr int kImageHeight = 512;

extern NkImage img;
extern std::mt19937 rng;
extern std::uniform_real_distribution<double> dist;
extern std::vector<Vec4d> cube;
extern std::vector<Vec2d> edges;
extern Vec3d eye;
extern Vec3d target;
extern Vec3d up;
extern Mat4d V;
extern Mat4d P;
