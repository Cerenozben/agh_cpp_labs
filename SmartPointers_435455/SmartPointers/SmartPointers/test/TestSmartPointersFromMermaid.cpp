
#include <SmartPointers/Graph.h>
#include <gtest/gtest.h>


class TestFromMermaid : public ::testing::TestWithParam<std::string>
{};

TEST_P(TestFromMermaid, Mermaid2Mermaid)
{
    using smartPointers::Graph;
    Graph graph;
    graph.fromMermaid(GetParam());
    EXPECT_EQ(graph.toMermaid(), GetParam());
}

INSTANTIATE_TEST_CASE_P(
        Mermaid2Mermaid,
        TestFromMermaid,
        ::testing::Values("flowchart LR\n",
                          "flowchart LR\n    node1\n",
                          "flowchart LR\n    node1\n    node2\n    node3\n",
                          "flowchart LR\n    node1\n    node2\n    node3\n    node1 --> node2\n",
                          "flowchart LR\n    node1\n    node2\n    node3\n    node1 --> node2\n    node2 --> node1\n",
                          "flowchart LR\n    node1\n    node2\n    node3\n    node1 --> node2\n    node2 --> node3\n"));