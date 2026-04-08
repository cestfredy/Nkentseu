#include "TestCommon.h"

TEST_CASE(Semaine2_TP3, Vec4dEtProjectionEtPerpectiveSimple) {
    std::vector<Vec2d> proj;
    std::vector<Vec4d> localCube = cube;

    double z_cam = 2.0;
    for (auto& p : localCube) {
        p.z += z_cam;
        proj.push_back(ProjectPoint(p));
    }

    img = NkImage(kImageWidth, kImageHeight);

    for (const auto& p : proj) {
        int x = (int)p.x;
        int y = (int)p.y;
        for (int dx = -2; dx <= 2; dx++) {
            for (int dy = -2; dy <= 2; dy++) {
                img.SetPixel(x + dx, y + dy, 255, 0, 0);
            }
        }
    }

    for (auto edge : edges) {
        img.DrawLine((int)proj[edge.x].x, (int)proj[edge.x].y, (int)proj[edge.y].x, (int)proj[edge.y].y);
    }
    img.SavePPM("cube.ppm");
}
