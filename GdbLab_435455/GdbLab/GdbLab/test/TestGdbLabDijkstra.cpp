
#include <GdbLab/Dijkstra.h>
#include <gtest/gtest.h>

#include <Watchdog.hpp>

namespace gdbLab
{
class DijkstraTest : public testing::Test
{
protected:
    void SetUp() override
    {
        auto watchdog = std::make_unique<Watchdog>(500);
        graph_ = std::make_unique<Graph>(9);
        graph_->addEdge(0, 1, 4);
        graph_->addEdge(0, 7, 8);
        graph_->addEdge(1, 2, 8);
        graph_->addEdge(1, 7, 11);
        graph_->addEdge(2, 3, 7);
        graph_->addEdge(2, 8, 2);
        graph_->addEdge(2, 5, 4);
        graph_->addEdge(3, 4, 9);
        graph_->addEdge(3, 5, 14);
        graph_->addEdge(4, 5, 10);
        graph_->addEdge(5, 6, 2);
        graph_->addEdge(6, 7, 1);
        graph_->addEdge(6, 8, 6);
        graph_->addEdge(7, 8, 7);
    }
    void TearDown() override { graph_ = nullptr; }

    std::unique_ptr<Graph> graph_{};
};

TEST_F(DijkstraTest, ShortestPath0Test)
{
    auto watchdog = std::make_unique<Watchdog>(500);
    auto distances = graph_->shortestPathsFromNode(0);
    EXPECT_EQ(0, distances[0]);
    EXPECT_EQ(4, distances[1]);
    EXPECT_EQ(12, distances[2]);
    EXPECT_EQ(19, distances[3]);
    EXPECT_EQ(21, distances[4]);
    EXPECT_EQ(11, distances[5]);
    EXPECT_EQ(9, distances[6]);
    EXPECT_EQ(8, distances[7]);
    EXPECT_EQ(14, distances[8]);
}

TEST_F(DijkstraTest, ShortestPath8Test)
{
    auto watchdog = std::make_unique<Watchdog>(500);
    auto distances = graph_->shortestPathsFromNode(8);
    EXPECT_EQ(14, distances[0]);
    EXPECT_EQ(10, distances[1]);
    EXPECT_EQ(2, distances[2]);
    EXPECT_EQ(9, distances[3]);
    EXPECT_EQ(16, distances[4]);
    EXPECT_EQ(6, distances[5]);
    EXPECT_EQ(6, distances[6]);
    EXPECT_EQ(7, distances[7]);
    EXPECT_EQ(0, distances[8]);
}

}  // namespace gdbLab