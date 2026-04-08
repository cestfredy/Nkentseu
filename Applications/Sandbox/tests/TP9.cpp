#include "TestCommon.h"

TEST_CASE(Semaine3_TP3, TRSEtDecomposition) {
    dist = std::uniform_real_distribution<double>(-5.0, 5.0);

    for (int t = 0; t < 20; t++) {
        Vec3d outT{dist(rng), dist(rng), dist(rng)};
        Vec3d outR{dist(rng), dist(rng), dist(rng)};
        Vec3d outS{dist(rng) + 6, dist(rng) + 6, dist(rng) + 6};

        Mat4d M = TRS(outT, outR, outS);

        Vec3d T2, R2, S2;
        DecomposeTRS(M, T2, R2, S2);

        ASSERT_TRUE(ApproxVec(outT, T2));
        ASSERT_TRUE(ApproxVec(outS, S2));
        ASSERT_TRUE(ApproxVec(outR, R2, 5.0));
    }
}
