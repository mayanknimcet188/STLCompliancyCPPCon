#include <iostream>
#include <string>
#include "graph_node.hpp"
#include "directed_graph.hpp"
#include "const_directed_graph_iterator.hpp"

template <typename T>
void to_dot(const directed_graph<T> &graph, std::string graph_name)
{
    std::cout << "digraph" << graph_name << "{" << std::endl;
    // for (size_t index = 0; index < graph.size(); ++index)
    // {
    //     const auto &node_value = graph[index];
    //     const auto adjacent_nodes = graph.get_adjacent_node_values(node_value);
    //     if (adjacent_nodes.empty())
    //     {
    //         std::cout << node_value << std::endl;
    //     }
    //     else
    //     {
    //         for (auto &&node : adjacent_nodes)
    //         {
    //             std::cout << node_value << " -> " << node << std::endl;
    //         }
    //     }
    // }

    for (auto &&node : graph)
    {

        const auto adjacent_nodes = graph.get_adjacent_node_values(node);
        const auto b = adjacent_nodes.cbegin();
        const auto e = adjacent_nodes.cend();
        if (b == e)
        {
            std::cout << node << std::endl;
        }
        else
        {
            for (auto iter = b; iter != e; ++iter)
            {
                std::cout << node << " -> " << *iter << std::endl;
            }
        }
    }
    std::cout << "}" << std::endl;
}

// standalone swap function
template <typename T>
void swap(directed_graph<T> &first, directed_graph<T> &second)
{
    first.swap(second);
}

// Driver code
int main()
{
    directed_graph<int> graph{11, 22, 33, 44, 55};
    graph.insert_edge(11, 33);
    graph.insert_edge(22, 33);
    graph.insert_edge(22, 44);
    graph.insert_edge(22, 55);
    graph.insert_edge(33, 44);
    graph.insert_edge(44, 55);

    to_dot(graph, "Graph1");

    graph.erase_edge(22, 44);
    graph.erase(std::find(std::begin(graph), std::end(graph), 44));

    to_dot(graph, "Graph1");
    return 0;
}