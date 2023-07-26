#ifndef GRAPH_NODE_HPP
#define GRAPH_NODE_HPP
#include <set>
// Grpah Node Implementation
template <typename T>
class graph_node
{
public:
    using adjacency_list_type = std::set<std::size_t>;
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
#endif