#include "TestCommon.h"

TEST_CASE(Semaine3_TP1, Mat4dEtInverse) {
    Mat4d m, r, inv;

    for (int t = 0; t < 10; t++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m(i, j) = dist(rng);
            }
        }

        r = m * Mat4d::Identity();
        ASSERT_TRUE(ApproxMat(r, m));

        if (Inverse(m, inv)) {
            ASSERT_TRUE(ApproxMat(m * inv, Mat4d::Identity(), 1e-10f));
        }
    }

    m = Mat4d::Identity();
    for (int j = 0; j < 4; j++) {
        m(1, j) = m(0, j);
    }
    ASSERT_TRUE(!Inverse(m, inv));

    r = Mat4d::RotateAxis({0, 1, 0}, NKENTSEU_PI_DOUBLE / 2.0f);
    Vec4d s = {1, 0, 0, 1};
    Vec4d q = r * s;

    ASSERT_TRUE(approxEq(q.x, 0.0));
    ASSERT_TRUE(approxEq(q.y, 0.0));
    ASSERT_TRUE(approxEq(q.z, -1.0));
}
