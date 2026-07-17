#include <GdbLab/Dijkstra.h>

#include <limits>
#include <queue>
#include <vector>

namespace gdbLab
{
// Allocates memory for adjacency list
Graph::Graph(size_t nodesCnt)
{
    adj_.resize(nodesCnt);
}

void Graph::addEdge(size_t srcNode, size_t dstNode, int weight)
{
    adj_[srcNode].push_back({dstNode, weight});
    adj_[dstNode].push_back({srcNode, weight});
}

// Prints shortest paths from src to all other vertices
std::vector<int> Graph::shortestPathsFromNode(size_t src)
{
    std::priority_queue<Route, std::vector<Route>, std::greater<>> pq;

    // Create a vector for distances and initialize all
    std::vector<int> dist(adj_.size(), std::numeric_limits<int>::max());

    // Insert source itself in priority queue and initialize
    // its distance as 0.
    pq.push({src, 0});

    dist[src] = 0;

    while (!pq.empty())
    {
        auto srcNode = pq.top().dstNode;
        pq.pop();

        // get all adjacent vertices of a vertex
        for (auto route : adj_[srcNode])
        {
            // Get vertex label and weight of current adjacent of srcNode.
            auto [dstNode, weight] = route;

            // If there is shorted path to dstNode through srcNode.
            if (dist[dstNode] > dist[srcNode] + weight)
            {
                // Updating distance of dstNode
                dist[dstNode] = dist[srcNode] + weight;
                pq.push({dstNode, dist[dstNode]});
            }
        }
    }

    return dist;
}

}  // namespace gdbLab
