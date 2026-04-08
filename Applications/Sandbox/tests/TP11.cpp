#include "TestCommon.h"

TEST_CASE(Semaine4_TP2, AnimationSLERP) {
    Quat q1, q2;

    q1 = FromAxisAngle({0, 1, 0}, 0);
    q2 = FromAxisAngle({0, 1, 0}, NKENTSEU_PI_DOUBLE);

    for (int frame = 0; frame < 60; frame++) {
        double t = frame / 59.0;
        Quat q = Slerp(q1, q2, t);
        Mat4d R = FromRT(ToMat3(q), {0, 0, 0});

        img = NkImage(kImageWidth, kImageHeight);
        std::vector<Vec3d> screen;
        for (auto v : cube) {
            Vec4d p = P * (V * (R * v));
            screen.push_back(ProjectToScreen(p, kImageWidth, kImageHeight));
        }

        for (auto edge : edges) {
            img.DrawLine((int)screen[edge.x].x, (int)screen[edge.x].y, (int)screen[edge.y].x, (int)screen[edge.y].y, 255);
        }
        img.SavePPM("Slerp__frame_TP11_" + std::to_string(frame) + ".ppm");
    }

    for (int frame = 0; frame < 60; frame++) {
        double t = frame / 59.0;
        Quat q = Lerp(q1, q2, t);
        Mat4d R = FromRT(ToMat3(q), {0, 0, 0});

        img = NkImage(kImageWidth, kImageHeight);
        std::vector<Vec3d> screen;
        for (auto v : cube) {
            Vec4d p = P * (V * (R * v));
            screen.push_back(ProjectToScreen(p, kImageWidth, kImageHeight));
        }

        for (auto edge : edges) {
            img.DrawLine((int)screen[edge.x].x, (int)screen[edge.y].y, (int)screen[edge.y].x, (int)screen[edge.y].y, 255);
        }
        img.SavePPM("Lerp__frame_TP11_" + std::to_string(frame) + ".ppm");
    }
}
