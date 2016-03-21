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

TEST(Sorteermethode, test_shellsort_int)
{
    Sortvector<int> vec(100);
    Sortvector<int> sorted(100);
    sorted.vul_range();
    vec.vul_random_zonder_dubbels();
    ShellSort<int> ss;
    ss(vec);
    for(int i=0;i<vec.size();i++)
    {
        EXPECT_EQ(sorted[i],vec[i]);
    }
}

TEST(Sorteermethode, test_shellshellsort_int)
{
    Sortvector<int> vec(100);
    Sortvector<int> sorted(100);
    sorted.vul_range();
    vec.vul_random_zonder_dubbels();
    ShellShellSort<int> ss;
    ss(vec);
    for(int i=0;i<vec.size();i++)
    {
        EXPECT_EQ(sorted[i],vec[i]);
    }
}

TEST(Sorteermethode, test_quicksort_int)
{
    Sortvector<int> vec(100);
    Sortvector<int> sorted(100);
    sorted.vul_range();
    vec.vul_random_zonder_dubbels();
    Quicksort<int> qs;
    qs(vec);
    for(int i=0;i<vec.size();i++)
    {
        EXPECT_EQ(sorted[i],vec[i]);
    }
}
