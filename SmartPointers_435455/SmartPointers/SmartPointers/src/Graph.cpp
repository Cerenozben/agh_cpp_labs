
#include <SmartPointers/Graph.h>

#include <regex>

namespace smartPointers
{
// student code begin
void Graph::addEdge(const std::string &fromLabel, const std::string &toLabel)
{
    GraphNodePtr fromNode = nullptr;
    GraphNodePtr toNode = nullptr;

    for (const auto &node : nodes_)
    {
        if (node->getLabel() == fromLabel)
        {
            fromNode = node;
        }
        if (node->getLabel() == toLabel)
        {
            toNode = node;
        }
    }
    if (!fromNode)
    {
        fromNode = std::make_shared<GraphNode>(fromLabel);
        nodes_.push_back(fromNode);
    }
    if (!toNode)
    {
        toNode = std::make_shared<GraphNode>(toLabel);
        nodes_.push_back(toNode);
    }
    fromNode->addEdge(toNode);
}

std::string Graph::toMermaid() const
{
    std::string result = "flowchart LR\n";
    for (const auto &node : nodes_)
    {
        result += "    " + node->getLabel() + "\n";
    }

    for (const auto &node : nodes_)
    {
        for (const auto &edge : node->getEdges())
        {
            result += "    " + node->getLabel() + " --> " + edge->getLabel() + "\n";
        }
    }

    return result;
}

void Graph::fromMermaid(const std::string &mermaidStr)
{
    std::regex edgeRegex(R"((\w+)\s*-->\s*(\w+))");
    std::regex nodeRegex(R"(^\s*(\w+)\s*$)");
    size_t start = 0;
    while (start < mermaidStr.length())
    {
        size_t end = mermaidStr.find('\n', start);
        std::string line;

        if (end != std::string::npos)
        {
            line = mermaidStr.substr(start, end - start);
            start = end + 1;
        }
        else
        {
            line = mermaidStr.substr(start);
            start = mermaidStr.length();
        }

        if (line.find("flowchart LR") != std::string::npos || line.find("graph LR") != std::string::npos)
        {
            continue;
        }

        std::smatch match;
        if (std::regex_search(line, match, edgeRegex))
        {
            addEdge(match[1].str(), match[2].str());
        }
        else if (std::regex_search(line, match, nodeRegex))
        {
            std::string label = match[1].str();
            bool exists = false;

            for (const auto &n : nodes_)
            {
                if (n->getLabel() == label)
                {
                    exists = true;
                    break;
                }
            }

            if (!exists)
            {
                nodes_.push_back(std::make_shared<GraphNode>(label));
            }
        }
    }
}
// student code end

}  // namespace smartPointers