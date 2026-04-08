#include "TestCommon.h"

TEST_CASE(Semaine1_TP3, TestsSurFloath) {
    ASSERT_TRUE(!isFiniteValid(std::numeric_limits<float>::quiet_NaN()));
    ASSERT_TRUE(!isFiniteValid(std::numeric_limits<float>::infinity()));
    ASSERT_TRUE(!isFiniteValid(-std::numeric_limits<float>::infinity()));
    ASSERT_TRUE(isFiniteValid(0.0f));
    ASSERT_TRUE(isFiniteValid(1.0f));

    ASSERT_TRUE(nearlyZero(0.0f, 1e-6f));
    ASSERT_TRUE(!nearlyZero(1e-5f, 1e-6f));
    ASSERT_TRUE(nearlyZero(1e-7f, 1e-6f));
    ASSERT_TRUE(nearlyZero(-1e-7f, 1e-6f));
    ASSERT_TRUE(!nearlyZero(-1e-6f, 1e-7f));
    ASSERT_TRUE(nearlyZero(1e-3f, 1e-2f));
    ASSERT_TRUE(!nearlyZero(1e-2f, 1e-3f));
    ASSERT_TRUE(nearlyZero(5e-8f, 1e-7f));

    ASSERT_TRUE(approxEq(1.0f, 1.0f, 1e-6f));
    ASSERT_TRUE(approxEq(1.0f, 1.0000001f, 1e-5f));
    ASSERT_TRUE(!approxEq(1.0f, 1.1f, 1e-3f));
    ASSERT_TRUE(approxEq(0.0f, 1e-7f, 1e-6f));
    ASSERT_TRUE(!approxEq(0.0f, 1e-4f, 1e-6f));
    ASSERT_TRUE(approxEq(-1.0f, -1.000001f, 1e-5f));
    ASSERT_TRUE(!approxEq(-1.0f, -1.1f, 1e-2f));
    ASSERT_TRUE(approxEq(1000.0f, 1000.0001f, 1e-3f));
    ASSERT_TRUE(approxEq(1000.0f, 1001.0f, 1e-3f));
    ASSERT_TRUE(approxEq(1e-7f, 2e-7f, 1e-6f));

    float s1, s2;
    std::vector<float> v;

    v = std::vector<float>(1000, 0.1f);
    s1 = std::accumulate(v.begin(), v.end(), 0.0f);
    s2 = kahanSum(v);
    ASSERT_TRUE(std::fabs(s2 - 100.0f) < std::fabs(s1 - 100.0f));

    v = std::vector<float>(10000, 0.1f);
    s1 = std::accumulate(v.begin(), v.end(), 0.0f);
    s2 = kahanSum(v);
    ASSERT_TRUE(std::fabs(s2 - 1000.0f) < std::fabs(s1 - 1000.0f));

    v = std::vector<float>({1e8f, 1.0f, -1e8f});
    s1 = std::accumulate(v.begin(), v.end(), 0.0f);
    s2 = kahanSum(v);
    ASSERT_TRUE(std::fabs(s2 - 1.0f) <= std::fabs(s1 - 1.0f));

    v = std::vector<float>({1.0f, 1e8f, -1e8f});
    s1 = std::accumulate(v.begin(), v.end(), 0.0f);
    s2 = kahanSum(v);
    ASSERT_TRUE(std::fabs(s2 - 1.0f) <= std::fabs(s1 - 1.0f));

    v = std::vector<float>(100000, 0.01f);
    s2 = kahanSum(v);
    ASSERT_TRUE(approxEq(s2, 1000.0f, 1e-2f));

    v = std::vector<float>(100000, 1e-5f);
    s2 = kahanSum(v);
    ASSERT_TRUE(approxEq(s2, 1.0f, 1e-3f));

    v = std::vector<float>({0.1f, 0.2f, 0.3f});
    s2 = kahanSum(v);
    ASSERT_TRUE(approxEq(s2, 0.6f, 1e-6f));

    v = std::vector<float>(50000, 0.2f);
    s2 = kahanSum(v);
    ASSERT_TRUE(approxEq(s2, 10000.0f, 1e-2f));

    v = std::vector<float>({1e7f, 1.0f, 1.0f, -1e7f});
    s2 = kahanSum(v);
    ASSERT_TRUE(approxEq(s2, 2.0f, 1e-3f));

    v = std::vector<float>(1000000, 0.1f);
    s2 = kahanSum(v);
    ASSERT_TRUE(approxEq(s2, 100000.0f, 1e-1f));
}
