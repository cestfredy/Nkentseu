#include "TestCommon.h"

TEST_CASE(Semaine2_TP1, Vec2dEtImpl) {
    ASSERT_TRUE(Dot({1, 0}, {0, 1}) == 0.0);
    ASSERT_TRUE(Dot({1, 0}, {1, 0}) == 1.0);
    ASSERT_TRUE(Dot({3, 4}, {3, 4}) == 25.0);
    ASSERT_TRUE(Dot({-1, 0}, {1, 0}) == -1.0);
    ASSERT_TRUE(Dot({2, 3}, {4, 5}) == 23.0);
    ASSERT_TRUE(Dot({0, 0}, {5, 7}) == 0.0);

    ASSERT_TRUE(Cross2D({1, 0}, {0, 1}) == 1.0);
    ASSERT_TRUE(Cross2D({0, 1}, {1, 0}) == -1.0);
    ASSERT_TRUE(Cross2D({1, 1}, {1, 1}) == 0.0);
    ASSERT_TRUE(Cross2D({2, 0}, {0, 2}) == 4.0);

    Vec2d w = {3, 4};
    Vec2d n = w.Normalized();
    ASSERT_TRUE(std::fabs(n.Norm() - 1.0) < kEps);
    ASSERT_TRUE(std::fabs(n.x - 0.6) < kEps);
    ASSERT_TRUE(std::fabs(n.y - 0.8) < kEps);

    Vec2d u = {1, 0};
    u = u.Normalized();
    ASSERT_TRUE(std::fabs(u.x - 1.0) < kEps);

    w = {10, 20};
    ASSERT_TRUE(w[0] == 10.0);
    ASSERT_TRUE(w[1] == 20.0);

    w[0] = 30;
    ASSERT_TRUE(w.x == 30.0);

    w[1] = 40;
    ASSERT_TRUE(w.y == 40.0);

    u = {5, 6};
    ASSERT_TRUE(u[0] == 5.0);

    static_assert(sizeof(Vec2d) == 16, "Vec2d must be 16 bytes");
}
