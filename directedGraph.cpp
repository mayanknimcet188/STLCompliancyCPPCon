#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <string_view>
#include <algorithm>
#include <string>

// Grpah Node Implementation
template <typename T>
class graph_node
{
public:
    using adjacency_list_type = std::set<size_t>;
    T m_data;
    adjacency_list_type m_adjacentNodeIndices;
    explicit graph_node(const T &t);
    explicit graph_node(T &&t);

    T &get() noexcept;
    const T &get() const noexcept;

    adjacency_list_type &get_adjacent_node_indices();
    const adjacency_list_type &get_adjacent_node_indices() const;

    bool operator==(const graph_node &rhs) const;
    bool operator!=(const graph_node &rhs) const;

    void swap(graph_node &other_node) noexcept;
};

template <typename T>
typename graph_node<T>::adjacency_list_type &graph_node<T>::get_adjacent_node_indices()
{
    return m_adjacentNodeIndices;
}

template <typename T>
const typename graph_node<T>::adjacency_list_type &graph_node<T>::get_adjacent_node_indices() const
{
    return m_adjacentNodeIndices;
}

template <typename T>
graph_node<T>::graph_node(const T &t) : m_data(t) {}

template <typename T>
graph_node<T>::graph_node(T &&t) : m_data(std::move(t)) {}

template <typename T>
T &graph_node<T>::get() noexcept
{
    return m_data;
}

template <typename T>
const T &graph_node<T>::get() const noexcept
{
    return m_data;
}

template <typename T>
bool graph_node<T>::operator==(const graph_node &rhs) const
{
    return m_data == rhs.m_data && m_adjacentNodeIndices == rhs.m_adjacentNodeIndices;
}

template <typename T>
bool graph_node<T>::operator!=(const graph_node &rhs) const
{
    return !(*this == rhs);
}

template <typename T>
void graph_node<T>::swap(graph_node &other_node) noexcept
{
    using std::swap;

    swap(m_data, other_node.m_data);
    swap(m_adjacentNodeIndices, other_node.m_adjacentNodeIndices);
}

// DIrected Graph Implementation
template <typename T>
class directed_graph
{
private:
    using nodes_container_type = std::vector<graph_node<T>>;
    nodes_container_type m_nodes;

    typename nodes_container_type::iterator find(const T &node_value);
    typename nodes_container_type::const_iterator find(const T &node_value) const;

    void remove_all_links_to(typename nodes_container_type::const_iterator node);

    std::set<T> get_adjacent_node_values(const typename graph_node<T>::adjacency_list_type &indices) const;

public:
    // For an insert to be successful, the value should not be in the graph yet.
    // Returns true if a new node with given value has been added to
    // the graph, and false if there was already a node with the given value.
    bool insert(const T &node_value);
    bool insert(T &&node_value);

    // Returns true if the given node value was erased, false otherwise
    bool erase(const T &node_value);

    // Returns true if the edge was successfully created, false otherwise
    bool insert_edge(const T &from_node_value, const T &to_node_value);

    // Returns true if the given edge was erased, false otherwise
    bool erase_edge(const T &from_node_value, const T &to_node_value);

    void clear() noexcept;

    T &operator[](size_t index);
    const T &operator[](size_t index) const;

    // Two directed graphs are equal if they have the same nodes and edges.
    // The order in which the nodes and edges have been added does not affect equality.
    bool operator==(const directed_graph &rhs) const;
    bool operator!=(const directed_graph &rhs) const;

    void swap(directed_graph &other_graph) noexcept;
    size_t size() const noexcept;

    // Returns a set with the nodes adjacent to the given node.
    std::set<T> get_adjacent_node_values(const T &node_value) const;
};

template <typename T>
typename directed_graph<T>::nodes_container_type::iterator directed_graph<T>::find(const T &node_value)
{
    return std::find_if(std::begin(m_nodes), std::end(m_nodes), [&node_value](const auto &node)
                        { return node.get() == node_value; });
}

template <typename T>
typename directed_graph<T>::nodes_container_type::const_iterator directed_graph<T>::find(const T &node_value) const
{
    return const_cast<directed_graph<T> *>(this)->find(node_value);
}

template <typename T>
std::set<T> directed_graph<T>::get_adjacent_node_values(const typename graph_node<T>::adjacency_list_type &indices) const
{
    std::set<T> values;
    for (auto &&index : indices)
    {
        values.insert(m_nodes[index].get());
    }
    return values;
}

template <typename T>
void directed_graph<T>::remove_all_links_to(typename nodes_container_type::const_iterator node)
{
    const size_t node_index = std::distance(std::cbegin(m_nodes), node);
    for (auto &&node : m_nodes)
    { // Iterate over all adjacency lists.
        // First remove references to the to-be-deleted node.
        auto &adjacencyIndices = node.get_adjacent_node_indices();
        adjacencyIndices.erase(node_index);
        // Second, modify all remaining adjacency indices to account for the removal of a node.
        for (auto iter = std::begin(adjacencyIndices); iter != std::end(adjacencyIndices);)
        {
            auto index = *iter;
            if (index > node_index)
            {
                auto hint = iter;
                ++hint;
                iter = adjacencyIndices.erase(iter);
                adjacencyIndices.insert(hint, index - 1);
            }
            else
            {
                ++iter;
            }
        }
    }
}

template <typename T>
size_t directed_graph<T>::size() const noexcept
{
    return m_nodes.size();
}

template <typename T>
bool directed_graph<T>::insert(T &&node_value)
{
    auto iter = find(node_value);
    if (iter != std::end(m_nodes))
    {
        return false; // value is already in the graph, return false.
    }
    m_nodes.emplace_back(std::move(node_value));
    return true; // Value successfully added to the graph, return true.
}

template <typename T>
bool directed_graph<T>::insert(const T &node_value)
{
    T copy(node_value);
    return insert(std::move(copy));
}

template <typename T>
bool directed_graph<T>::erase(const T &node_value)
{
    auto iter = find(node_value);
    if (iter == std::end(m_nodes))
    {
        return false; // Value not in the graph, return false.
    }
    remove_all_links_to(iter);
    m_nodes.erase(iter);
    return true;
}

template <typename T>
void directed_graph<T>::clear() noexcept
{
    m_nodes.clear();
}

template <typename T>
bool directed_graph<T>::insert_edge(const T &from_node_value, const T &to_node_value)
{
    const auto from = find(from_node_value);
    const auto to = find(to_node_value);
    if (from == std::end(m_nodes) || to == std::end(m_nodes))
    {
        return false;
    }

    const size_t to_index = std::distance(std::begin(m_nodes), to);
    return from->get_adjacent_node_indices().insert(to_index).second;
}

template <typename T>
bool directed_graph<T>::erase_edge(const T &from_node_value, const T &to_node_value)
{
    const auto from = find(from_node_value);
    const auto to = find(to_node_value);
    if (from == std::end(m_nodes) || to == std::end(m_nodes))
    {
        return false; // nothing to erase
    }

    const size_t to_index = std::distance(std::begin(m_nodes), to);
    from->get_adjacent_node_indices().erase(to_index);
    return true;
}

template <typename T>
T &directed_graph<T>::operator[](size_t index)
{
    return m_nodes[index].get();
}

template <typename T>
const T &directed_graph<T>::operator[](size_t index) const
{
    return m_nodes[index].get();
}

template <typename T>
std::set<T> directed_graph<T>::get_adjacent_node_values(const T &node_value) const
{
    auto iter = find(node_value);
    if (iter == std::end(m_nodes))
        return std::set<T>(); // return empty set if there is no such node

    return get_adjacent_node_values(iter->get_adjacent_node_indices());
}

template <typename T>
bool directed_graph<T>::operator==(const directed_graph &rhs) const
{
    for (auto &&node : m_nodes)
    {
        const auto result = rhs.find(node.get());
        if (result == std::end(rhs.m_nodes))
            return false;

        const auto adjacent_node_values_lhs = get_adjacent_node_values(node.get_adjacent_node_indices());
        const auto adjacent_node_values_rhs = rhs.get_adjacent_node_values(result->get_adjacent_node_indices());

        if (adjacent_node_values_lhs != adjacent_node_values_rhs)
            return false;
    }
    return true;
}

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