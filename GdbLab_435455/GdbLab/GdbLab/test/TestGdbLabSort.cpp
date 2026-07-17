
#include <GdbLab/Sort.h>
#include <gtest/gtest.h>

#include <Watchdog.hpp>

namespace gdbLab
{
class SortTest : public ::testing::TestWithParam<std::pair<std::vector<int>, std::vector<int>>>
{};

TEST_P(SortTest, BubbleSortTest)
{
    auto watchdog = std::make_unique<Watchdog>(500);
    std::vector<int> arr = GetParam().first;
    bubbleSort(arr);
    EXPECT_EQ(arr, GetParam().second);
}

TEST_P(SortTest, QuickSortTest)
{
    auto watchdog = std::make_unique<Watchdog>(500);
    std::vector<int> arr = GetParam().first;
    quickSort(arr);
    EXPECT_EQ(arr, GetParam().second);
}

TEST_P(SortTest, BucketTest)
{
    auto watchdog = std::make_unique<Watchdog>(500);
    std::vector<int> arr = GetParam().first;
    bucketSort(arr);
    EXPECT_EQ(arr, GetParam().second);
}

INSTANTIATE_TEST_CASE_P(SortTest,
                        SortTest,
                        ::testing::Values(std::pair<std::vector<int>, std::vector<int>>{{}, {}},
                                          std::pair<std::vector<int>, std::vector<int>>{{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}},
                                          std::pair<std::vector<int>, std::vector<int>>{{5, 4, 3, 2, 1}, {1, 2, 3, 4, 5}},
                                          std::pair<std::vector<int>, std::vector<int>>{{5, 2, 9, 1, 5, 6}, {1, 2, 5, 5, 6, 9}},
                                          std::pair<std::vector<int>, std::vector<int>>{{10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
                                                                                        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}},
                                          std::pair<std::vector<int>, std::vector<int>>{{9, 8, 7, 6, 5, 4, 4, 3, 2, 1},
                                                                                        {1, 2, 3, 4, 4, 5, 6, 7, 8, 9}}));

}  // namespace gdbLab