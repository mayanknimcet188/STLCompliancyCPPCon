#ifndef DIRECTED_GRAPH_HPP
#define DIRECTED_GRAPH_HPP
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include "graph_node.hpp"
#include "const_directed_graph_iterator.hpp"
#include "const_adjacent_nodes_iterator.hpp"
#include "adjacent_nodes_iterator.hpp"

// DIrected Graph Implementation
template <typename T>
class directed_graph
{
public:
    using nodes_container_type = std::vector<graph_node<T>>;
    nodes_container_type m_nodes;

    typename nodes_container_type::iterator find(const T &node_value);
    typename nodes_container_type::const_iterator find(const T &node_value) const;

    void remove_all_links_to(typename nodes_container_type::const_iterator node);

    std::set<T> get_adjacent_node_values(const typename graph_node<T>::adjacency_list_type &indices) const;

public:
    // public type aliases
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    // public iterator-related type aliases
    using iterator = const_directed_graph_iterator<directed_graph>;
    using const_iterator = const_directed_graph_iterator<directed_graph>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // ctor taking iterator range
    template <typename Iter>
    directed_graph(Iter first, Iter last);
    // ctors and assignment operator taking initializer list
    directed_graph(std::initializer_list<T> init);
    directed_graph<T> &operator=(std::initializer_list<T> init);
    using iterator_adjacent_nodes = adjacent_nodes_iterator<directed_graph>;
    using const_iterator_adjacent_nodes = const_adjacent_nodes_iterator<directed_graph>;
    using reverse_iterator_adjacent_nodes = std::reverse_iterator<iterator_adjacent_nodes>;
    using const_reverse_iterator_adjacent_nodes = std::reverse_iterator<const_iterator_adjacent_nodes>;

    // iterators for STL Compliancy
    iterator begin() noexcept;
    iterator end() noexcept;

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    // reverse iterators
    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;

    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rend() const noexcept;

    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    // return iterator to the list of adjacent nodes for the given node
    // return a default constructed iterator as the end iterator if the value is not found
    iterator_adjacent_nodes begin(const T &node_value) noexcept;
    iterator_adjacent_nodes end(const T &node_value) noexcept;

    const_iterator_adjacent_nodes begin(const T &node_value) const noexcept;
    const_iterator_adjacent_nodes end(const T &node_value) const noexcept;

    const_iterator_adjacent_nodes cbegin(const T &node_value) const noexcept;
    const_iterator_adjacent_nodes cend(const T &node_value) const noexcept;

    reverse_iterator_adjacent_nodes rbegin(const T &node_value) noexcept;
    reverse_iterator_adjacent_nodes rend(const T &node_value) noexcept;

    const_reverse_iterator_adjacent_nodes rbegin(const T &node_value) const noexcept;
    const_reverse_iterator_adjacent_nodes rend(const T &node_value) const noexcept;

    const_reverse_iterator_adjacent_nodes crbegin(const T &node_value) const noexcept;
    const_reverse_iterator_adjacent_nodes crend(const T &node_value) const noexcept;

    // For an insert to be successful, the value should not be in the graph yet.
    // Returns true if a new node with given value has been added to
    // the graph, and false if there was already a node with the given value.
    std::pair<iterator, bool> insert(const T &node_value);
    std::pair<iterator, bool> insert(T &&node_value);

    // Returns true if the given node value was erased, false otherwise
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);

    // Returns true if the edge was successfully created, false otherwise
    bool insert_edge(const T &from_node_value, const T &to_node_value);

    // Returns true if the given edge was erased, false otherwise
    bool erase_edge(const T &from_node_value, const T &to_node_value);

    // assign method
    template <typename Iter>
    void assign(Iter first, Iter last);
    void assign(std::initializer_list<T> init);

    void clear() noexcept;

    reference operator[](size_type index);
    const_reference operator[](size_type index) const;

    reference at(size_type index);
    const_reference at(size_type index) const;

    // Two directed graphs are equal if they have the same nodes and edges.
    // The order in which the nodes and edges have been added does not affect equality.
    bool operator==(const directed_graph &rhs) const;
    bool operator!=(const directed_graph &rhs) const;

    void swap(directed_graph &other_graph) noexcept;
    size_t size() const noexcept;

    size_type max_size() const noexcept;
    bool empty() const noexcept;

    // Returns a set with the nodes adjacent to the given node.
    std::set<T> get_adjacent_node_values(const T &node_value) const;
};

#include <set>

template <typename T>
template <typename Iter>
directed_graph<T>::directed_graph(Iter first, Iter last)
{
    assign(first, last);
}

template <typename T>
directed_graph<T>::directed_graph(std::initializer_list<T> init)
{
    assign(std::begin(init), std::end(init));
}

template <typename T>
directed_graph<T> &directed_graph<T>::operator=(std::initializer_list<T> init)
{
    clear();
    assign(std::begin(init), std::end(init));
    return *this;
}

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
typename directed_graph<T>::size_type directed_graph<T>::max_size() const noexcept
{
    return m_nodes.max_size();
}

template <typename T>
bool directed_graph<T>::empty() const noexcept
{
    return m_nodes.empty();
}

template <typename T>
typename directed_graph<T>::iterator directed_graph<T>::begin() noexcept
{
    return iterator(std::begin(m_nodes), this);
}

template <typename T>
typename directed_graph<T>::iterator directed_graph<T>::end() noexcept
{
    return iterator(std::end(m_nodes), this);
}

template <typename T>
typename directed_graph<T>::const_iterator directed_graph<T>::begin() const noexcept
{
    return const_cast<directed_graph *>(this)->begin();
}

template <typename T>
typename directed_graph<T>::const_iterator directed_graph<T>::end() const noexcept
{
    return const_cast<directed_graph *>(this)->end();
}

template <typename T>
typename directed_graph<T>::const_iterator directed_graph<T>::cbegin() const noexcept
{
    return const_cast<directed_graph *>(this)->begin();
}

template <typename T>
typename directed_graph<T>::const_iterator directed_graph<T>::cend() const noexcept
{
    return const_cast<directed_graph *>(this)->end();
}

template <typename T>
typename directed_graph<T>::reverse_iterator directed_graph<T>::rbegin() noexcept
{
    return reverse_iterator(end());
}

template <typename T>
typename directed_graph<T>::reverse_iterator directed_graph<T>::rend() noexcept
{
    return reverse_iterator(begin());
}

template <typename T>
typename directed_graph<T>::const_reverse_iterator directed_graph<T>::rbegin() const noexcept
{
    return const_cast<directed_graph *>(this)->rbegin();
}

template <typename T>
typename directed_graph<T>::const_reverse_iterator directed_graph<T>::rend() const noexcept
{
    return const_cast<directed_graph *>(this)->rend();
}

template <typename T>
typename directed_graph<T>::const_reverse_iterator directed_graph<T>::crbegin() const noexcept
{
    return const_cast<directed_graph *>(this)->rbegin();
}

template <typename T>
typename directed_graph<T>::const_reverse_iterator directed_graph<T>::crend() const noexcept
{
    return const_cast<directed_graph *>(this)->rend();
}

template <typename T>
typename directed_graph<T>::iterator_adjacent_nodes directed_graph<T>::begin(const T &node_value) noexcept
{
    auto iter = find(node_value);
    if (iter == std::end(m_nodes)) // return a default constructed end iterator
        return adjacent_nodes_iterator<directed_graph>();
    return adjacent_nodes_iterator<directed_graph>(std::begin(iter->get_adjacent_node_indices()), this);
}

template <typename T>
typename directed_graph<T>::iterator_adjacent_nodes directed_graph<T>::end(const T &node_value) noexcept
{
    auto iter = find(node_value);
    if (iter == std::end(m_nodes)) // return a default constructed end iterator
        return adjacent_nodes_iterator<directed_graph>();
    return adjacent_nodes_iterator<directed_graph>(std::end(iter->get_adjacent_node_indices()), this);
}

template <typename T>
typename directed_graph<T>::const_iterator_adjacent_nodes directed_graph<T>::begin(const T &node_value) const noexcept
{
    return const_cast<directed_graph *>(this)->begin(node_value);
}

template <typename T>
typename directed_graph<T>::const_iterator_adjacent_nodes directed_graph<T>::end(const T &node_value) const noexcept
{
    return const_cast<directed_graph *>(this)->end(node_value);
}

template <typename T>
typename directed_graph<T>::const_iterator_adjacent_nodes directed_graph<T>::cbegin(const T &node_value) const noexcept
{
    return const_cast<directed_graph *>(this)->begin(node_value);
}

template <typename T>
typename directed_graph<T>::const_iterator_adjacent_nodes directed_graph<T>::cend(const T &node_value) const noexcept
{
    return const_cast<directed_graph *>(this)->end(node_value);
}

template <typename T>
typename directed_graph<T>::reverse_iterator_adjacent_nodes directed_graph<T>::rbegin(const T &node_value) noexcept
{
    return reverse_iterator(end(node_value));
}

template <typename T>
typename directed_graph<T>::reverse_iterator_adjacent_nodes directed_graph<T>::rend(const T &node_value) noexcept
{
    return reverse_iterator(begin(node_value));
}

template <typename T>
typename directed_graph<T>::const_reverse_iterator_adjacent_nodes directed_graph<T>::rbegin(const T &node_value) const noexcept
{
    return const_cast<directed_graph *>(this)->rbegin(node_value);
}

template <typename T>
typename directed_graph<T>::const_reverse_iterator_adjacent_nodes directed_graph<T>::rend(const T &node_value) const noexcept
{
    return const_cast<directed_graph *>(this)->rend(node_value);
}

template <typename T>
typename directed_graph<T>::const_reverse_iterator_adjacent_nodes directed_graph<T>::crbegin(const T &node_value) const noexcept
{
    return const_cast<directed_graph *>(this)->rbegin(node_value);
}

template <typename T>
typename directed_graph<T>::const_reverse_iterator_adjacent_nodes directed_graph<T>::crend(const T &node_value) const noexcept
{
    return const_cast<directed_graph *>(this)->rend(node_value);
}

template <typename T>
std::pair<typename directed_graph<T>::iterator, bool> directed_graph<T>::insert(T &&node_value)
{
    auto iter = find(node_value);
    if (iter != std::end(m_nodes))
    {
        return std::make_pair(iterator(iter, this), false); // value is already in the graph, return false.
    }
    m_nodes.emplace_back(std::move(node_value));
    return std::make_pair(iterator(--std::end(m_nodes), this), true); // Value successfully added to the graph, return true.
}

template <typename T>
std::pair<typename directed_graph<T>::iterator, bool> directed_graph<T>::insert(const T &node_value)
{
    T copy(node_value);
    return insert(std::move(copy));
}

template <typename T>
typename directed_graph<T>::iterator directed_graph<T>::erase(const_iterator pos)
{

    if (pos.m_nodeIterator == std::end(m_nodes))
    {
        return iterator(std::end(m_nodes), this); // Value not in the graph, return end iterator.
    }

    remove_all_links_to(pos.m_nodeIterator);
    return iterator(m_nodes.erase(pos.m_nodeIterator), this);
}

template <typename T>
typename directed_graph<T>::iterator directed_graph<T>::erase(const_iterator first, const_iterator last)
{
    for (auto iter = first; iter != last; ++iter)
    {
        if (iter.m_nodeIterator != std::end(m_nodes))
        {
            remove_all_links_to(iter.m_nodeIterator);
        }
    }

    return iterator(m_nodes.erase(first.m_nodeIterator, last.m_nodeIterator), this);
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
template <typename Iter>
void directed_graph<T>::assign(Iter first, Iter last)
{
    clear();
    for (auto iter = first; iter != last; ++iter)
        insert(*iter);
}

template <typename T>
void directed_graph<T>::assign(std::initializer_list<T> init)
{
    assign(std::begin(init), std::end(init));
}

template <typename T>
typename directed_graph<T>::reference directed_graph<T>::operator[](size_type index)
{
    return m_nodes[index].get();
}

template <typename T>
typename directed_graph<T>::const_reference directed_graph<T>::operator[](size_type index) const
{
    return m_nodes[index].get();
}

template <typename T>
typename directed_graph<T>::reference directed_graph<T>::at(size_type index)
{
    return m_nodes.at(index).get();
}

template <typename T>
typename directed_graph<T>::const_reference directed_graph<T>::at(size_type index) const
{
    return m_nodes.at(index).get();
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
void directed_graph<T>::swap(directed_graph &other) noexcept
{
    swap(m_nodes, other.m_nodes);
}

template <typename T>
bool directed_graph<T>::operator!=(const directed_graph &rhs) const
{
    return !(*this == rhs);
}
#endif