#ifndef CONST_DIRECTED_GRAPH_ITERATOR_HPP
#define CONST_DIRECTED_GRAPH_ITERATOR_HPP
#include <iterator>

template <typename DirectedGraph>
class const_directed_graph_iterator
{
public:
    using value_type = typename DirectedGraph::value_type;
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = const value_type *;
    using reference = const value_type &;
    using iterator_type = typename DirectedGraph::nodes_container_type::const_iterator;

    // Bidirectional iterators must supply a default constructor
    const_directed_graph_iterator() = default;
    // no transfer of ownership of graph
    const_directed_graph_iterator(iterator_type it, const DirectedGraph *graph);

    reference operator*() const;
    pointer operator->() const;

    const_directed_graph_iterator &operator++();
    const_directed_graph_iterator operator++(int);

    const_directed_graph_iterator &operator--();
    const_directed_graph_iterator operator--(int);

    // The following are ok as member functions because we dont support
    // comparisons of different types to this one.
    bool operator==(const const_directed_graph_iterator &rhs) const;
    bool operator!=(const const_directed_graph_iterator &rhs) const;

public:
    iterator_type m_nodeIterator;
    const DirectedGraph *m_graph = nullptr;

    // Helper methods for operator++ and operator--
    void increment();
    void decrement();
};

// const_directed_graph_members implementation

template <typename DirectedGraph>
const_directed_graph_iterator<DirectedGraph>::const_directed_graph_iterator(iterator_type it, const DirectedGraph *graph) : m_nodeIterator(it), m_graph(graph) {}

template <typename DirectedGraph>
typename const_directed_graph_iterator<DirectedGraph>::reference const_directed_graph_iterator<DirectedGraph>::operator*() const
{
    return m_nodeIterator->get();
}

// Return a pointer to the actual element, so the compiler can
// apply -> to it to access the actual desired field
template <typename DirectedGraph>
typename const_directed_graph_iterator<DirectedGraph>::pointer const_directed_graph_iterator<DirectedGraph>::operator->() const
{
    return &(m_nodeIterator->get());
}

template <typename DirectedGraph>
const_directed_graph_iterator<DirectedGraph> &const_directed_graph_iterator<DirectedGraph>::operator++()
{
    increment();
    return *this;
}

template <typename DirectedGraph>
const_directed_graph_iterator<DirectedGraph> const_directed_graph_iterator<DirectedGraph>::operator++(int)
{
    auto oldIt = *this;
    increment();
    return oldIt;
}

template <typename DirectedGraph>
void const_directed_graph_iterator<DirectedGraph>::increment()
{
    ++m_nodeIterator;
}

template <typename DirectedGraph>
void const_directed_graph_iterator<DirectedGraph>::decrement()
{
    --m_nodeIterator;
}

template <typename DirectedGraph>
const_directed_graph_iterator<DirectedGraph> &const_directed_graph_iterator<DirectedGraph>::operator--()
{
    decrement();
    return *this;
}

template <typename DirectedGraph>
const_directed_graph_iterator<DirectedGraph> const_directed_graph_iterator<DirectedGraph>::operator--(int)
{
    auto oldIt = *this;
    decrement();
    return oldIt;
}

template <typename DirectedGraph>
bool const_directed_graph_iterator<DirectedGraph>::operator==(const const_directed_graph_iterator &rhs) const
{
    return this->m_nodeIterator == rhs.m_nodeIterator;
}

template <typename DirectedGraph>
bool const_directed_graph_iterator<DirectedGraph>::operator!=(const const_directed_graph_iterator &rhs) const
{
    return this->m_nodeIterator != rhs.m_nodeIterator;
}

#endif