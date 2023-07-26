#include <iostream>
#include <string>
#include "graph_node.hpp"
#include "directed_graph.hpp"

template <typename T>
void to_dot(const directed_graph<T> &graph, std::string graph_name)
{
    std::cout << "digraph" << graph_name << "{" << std::endl;
    for (size_t index = 0; index < graph.size(); ++index)
    {
        const auto &node_value = graph[index];
        const auto adjacent_nodes = graph.get_adjacent_node_values(node_value);
        if (adjacent_nodes.empty())
        {
            std::cout << node_value << std::endl;
        }
        else
        {
            for (auto &&node : adjacent_nodes)
            {
                std::cout << node_value << " -> " << node << std::endl;
            }
        }
    }
    std::cout << "}" << std::endl;
}

// Driver code
int main()
{
    directed_graph<int> graph;
    graph.insert(11);
    graph.insert(22);
    graph.insert(33);
    graph.insert(44);
    graph.insert(55);
    graph.insert_edge(11, 33);
    graph.insert_edge(22, 33);
    graph.insert_edge(22, 44);
    graph.insert_edge(22, 55);
    graph.insert_edge(33, 44);
    graph.insert_edge(44, 55);

    to_dot(graph, "Graph1");

    graph.erase_edge(22, 44);
    graph.erase(44);

    to_dot(graph, "Graph1");
    return 0;
}