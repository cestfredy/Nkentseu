#include "TestCommon.h"

TEST_CASE(Semaine3_TP2, RotationCube) {
    for (int frame = 0; frame < 10; frame++) {
        img = NkImage(kImageWidth, kImageHeight);
        double angle = frame * 0.3;
        Mat4d R = Mat4d::RotateAxis(up, angle);
        std::vector<Vec3d> screen;

        for (auto v : cube) {
            Vec4d p = P * (V * (R * v));
            screen.push_back(ProjectToScreen(p, kImageWidth, kImageHeight));
        }

        for (auto edge : edges) {
            img.DrawLine((int)screen[edge.x].x, (int)screen[edge.x].y, (int)screen[edge.y].x, (int)screen[edge.y].y, 255);
        }
        img.SavePPM("frame_TP8_" + std::to_string(frame) + ".ppm");
    }
}
