#include "TestCommon.h"

TEST_CASE(Semaine1_TP2, Precision) {
    float s1, s2;
    std::vector<float> v;

    std::vector<float> data(1'000'000, 0.1f);

    s1 = std::accumulate(data.begin(), data.end(), 0.0f);
    s2 = kahanSum(data);
    logger.Info("\nSum with accumulate : {0}\nKahan sum : {1}\nReal value : 100000.0", s1, s2);

    v = std::vector<float>({1e8f, 1e8f, 1.0f, 2.0f});
    logger.Info("\nVariance Naive   : {0}\nVariance Welford : {1}", varianceNaive(v), varianceWelford(v));

    logger.Info(
        "\nEpsilon Machine (loop) : {0}\nEpsilon Machine (std)  : {1}",
        epsilonMachine(),
        std::numeric_limits<float>::epsilon());
}
