#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace smartPointers
{
// student code begin
class GraphNode;
using GraphNodePtr = std::shared_ptr<GraphNode>;

class GraphNode
{
public:
    explicit GraphNode(std::string label) : label_(std::move(label)), edges_() {}

    void addEdge(const GraphNodePtr &node) { edges_.push_back(node); }

    std::string getLabel() const { return label_; }
    std::vector<GraphNodePtr> getEdges() const { return edges_; }

private:
    std::string label_;

    std::vector<GraphNodePtr> edges_;
};

class Graph
{
private:
    std::vector<GraphNodePtr> nodes_;

public:
    Graph() : nodes_() {}
    void addNode(const GraphNodePtr &node) { nodes_.push_back(node); }
    const std::vector<GraphNodePtr> &getNodes() const { return nodes_; }

    void addEdge(const std::string &fromLabel, const std::string &toLabel);
    std::string toMermaid() const;
    void fromMermaid(const std::string &mermaidStr);
};
// student code end

}  // namespace smartPointers
