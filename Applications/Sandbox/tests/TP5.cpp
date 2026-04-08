#include "TestCommon.h"

TEST_CASE(Semaine2_TP2, Vec3dEtGramSchmidt) {
    Vec3d i = {1, 0, 0};
    Vec3d j = {0, 1, 0};
    Vec3d k = {0, 0, 1};

    ASSERT_TRUE(ApproxVec(Cross(i, j), k));
    ASSERT_TRUE(ApproxVec(Cross(j, i), {0, 0, -1}));
    ASSERT_TRUE(ApproxVec(Cross(j, k), i));
    ASSERT_TRUE(ApproxVec(Cross(k, i), j));
    ASSERT_TRUE(approxEq(Dot(Cross(i, j), i), 0));
    ASSERT_TRUE(approxEq(Dot(Cross(i, j), j), 0));

    for (int t = 0; t < 10; ++t) {
        Vec3d a{dist(rng), dist(rng), dist(rng)};
        Vec3d b{dist(rng), dist(rng), dist(rng)};
        Vec3d c{dist(rng), dist(rng), dist(rng)};

        Vec3d ui = a.Normalized();
        Vec3d vi = (b - Project(b, ui)).Normalized();
        Vec3d wi = (c - Project(c, ui) - Project(c, vi)).Normalized();

        ASSERT_TRUE(approxEq(ui.Norm(), 1.0));
        ASSERT_TRUE(approxEq(vi.Norm(), 1.0));
        ASSERT_TRUE(approxEq(wi.Norm(), 1.0));

        ASSERT_TRUE(approxEq(Dot(ui, vi), 0.0));
        ASSERT_TRUE(approxEq(Dot(ui, wi), 0.0));
        ASSERT_TRUE(approxEq(Dot(vi, wi), 0.0));
    }

    i = {3, 4, 0};
    j = {1, 0, 0};
    Vec3d proj = Project(i, j);
    Vec3d rej = Reject(i, j);
    ASSERT_TRUE(ApproxVec(proj + rej, i));
}
