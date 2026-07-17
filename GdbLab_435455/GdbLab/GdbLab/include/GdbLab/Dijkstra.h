#pragma once
#include <list>
#include <vector>

namespace gdbLab
{
using NodeId = size_t;

struct Route
{
    NodeId dstNode;
    int weight;
    bool operator>(const Route &rhs) const { return weight > rhs.weight; }
    bool operator<(const Route &rhs) const { return rhs.weight > weight; }
};

// This class represents a directed graph using
// adjacency list representation
class Graph
{
    std::vector<std::list<Route>> adj_{};

public:
    explicit Graph(size_t nodesCnt);

    // function to add an edge to graph
    void addEdge(size_t srcNode, size_t dstNode, int weight);

    // prints shortest path from s
    std::vector<int> shortestPathsFromNode(size_t src);
};

}  // namespace gdbLab
