#include "gtest/gtest.h"
#include "../src/sortvector.h"
#include "../src/sorteermethode.h"

TEST(Sortvector, vul_range_test)
{
    Sortvector<int> sv(6);
    sv.vul_range();
    for(int i=0;i<6;i++)
        EXPECT_EQ(sv[i], i);
}


TEST(Sortvector, vul_omgekeerd_test)
{
    Sortvector<int> sv(6);
    sv.vul_range();
    sv.draai_om();
    for(int i=0;i<6;i++)
        EXPECT_EQ(sv[i], sv.size()-i-1);
}
