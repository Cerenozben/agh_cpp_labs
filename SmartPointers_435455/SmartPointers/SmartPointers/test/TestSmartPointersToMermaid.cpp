
#include <SmartPointers/Graph.h>
#include <gtest/gtest.h>

std::string demangle(const char *name);
std::string demangle(const char *name)
{
    int status = -4;
    std::unique_ptr<char, void (*)(void *)> res{abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free};
    return (status == 0) ? res.get() : name;
}

TEST(TestGraph, Const)
{
    using smartPointers::Graph;
    const Graph graph;
    graph.toMermaid();
}

TEST(TestGraph, EmptyGraph)
{
    using smartPointers::Graph;
    Graph graph;
    ASSERT_EQ(graph.toMermaid(), "flowchart LR\n");
}

TEST(TestGraph, SingleNode)
{
    using smartPointers::Graph;
    using smartPointers::GraphNode;
    using smartPointers::GraphNodePtr;
    Graph graph;
    GraphNodePtr node1(new GraphNode("node1"));
    graph.addNode(node1);
    ASSERT_EQ(graph.toMermaid(), R"(flowchart LR
    node1
)");
}

TEST(TestGraph, MultipleNodes)
{
    using smartPointers::Graph;
    using smartPointers::GraphNode;
    using smartPointers::GraphNodePtr;
    Graph graph;
    GraphNodePtr node1(new GraphNode("node1"));
    GraphNodePtr node2(new GraphNode("node2"));
    GraphNodePtr node3(new GraphNode("node3"));
    graph.addNode(node1);
    graph.addNode(node2);
    graph.addNode(node3);
    ASSERT_EQ(graph.toMermaid(), R"(flowchart LR
    node1
    node2
    node3
)");
}
TEST(TestGraph, Edges)
{
    using smartPointers::Graph;
    using smartPointers::GraphNode;
    using smartPointers::GraphNodePtr;
    Graph graph;
    GraphNodePtr node1(new GraphNode("node1"));
    GraphNodePtr node2(new GraphNode("node2"));
    GraphNodePtr node3(new GraphNode("node3"));
    node1->addEdge(node2);
    node2->addEdge(node3);
    graph.addNode(node1);
    graph.addNode(node2);
    graph.addNode(node3);
    ASSERT_EQ(graph.toMermaid(), "flowchart LR\n    node1\n    node2\n    node3\n    node1 --> node2\n    node2 --> node3\n");
}