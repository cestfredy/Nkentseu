#include "TestCommon.h"

TEST_CASE(Semaine4_TP1, Quaternions) {
    Mat3d m1, m2, m3;
    Quat q1, q2, q3;

    Vec3d i = {1, 0, 0};
    q1 = FromAxisAngle({0, 1, 0}, NKENTSEU_PI_DOUBLE / 2.0f);
    Vec3d j = Rotate(q1, i);

    ASSERT_TRUE(std::fabs(j.x - 0.0) < kEps);
    ASSERT_TRUE(std::fabs(j.y - 0.0) < kEps);
    ASSERT_TRUE(std::fabs(j.z + 1.0) < kEps);

    dist = std::uniform_real_distribution<double>(-1.0, 1.0);

    for (int t = 0; t < 50; t++) {
        q1 = {dist(rng), dist(rng), dist(rng), dist(rng)};
        q1 = q1.Normalized();

        m1 = ToMat3(q1);
        q2 = FromMat3(m1);
        q2 = q2.Normalized();

        ASSERT_TRUE(ApproxQuat(q1, q2, 1e-4f));
    }

    for (int t = 0; t < 50; t++) {
        q1 = {dist(rng), dist(rng), dist(rng), dist(rng)};
        q1 = q1.Normalized();
        q2 = q1.Inverse();
        q3 = q1 * q2;
        ASSERT_TRUE(ApproxQuat(q3, Quat::Identity(), 1e-4f));
    }
}
