#ifndef ADJACENT_NODES_ITERATOR_HPP
#define ADJACENT_NODES_ITERATOR_HPP
#include <iterator>
#include "const_adjacent_nodes_iterator.hpp"
#include "graph_node.hpp"

template <typename DirectedGraph>
class adjacent_nodes_iterator : public const_adjacent_nodes_iterator<DirectedGraph>
{
public:
    using value_type = typename DirectedGraph::value_type;
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = value_type *;
    using reference = value_type &;
    using iterator_type = typename std::set<value_type>::iterator;

    adjacent_nodes_iterator();
    adjacent_nodes_iterator(iterator_type it, const DirectedGraph *graph);

    reference operator*();
    pointer operator->();
    adjacent_nodes_iterator &operator++();
    adjacent_nodes_iterator &operator++(int);
    adjacent_nodes_iterator &operator--();
    adjacent_nodes_iterator &operator--(int);
};

template <typename DirectedGraph>
adjacent_nodes_iterator<DirectedGraph>::adjacent_nodes_iterator()
{
    this->m_nodeIterator = std::set<value_type>::end(); // return default constructed iterator as end iterator for no node value found
}

template <typename DirectedGraph>
adjacent_nodes_iterator<DirectedGraph>::adjacent_nodes_iterator(iterator_type it, const DirectedGraph *graph)
{
    this->const_directed_graph_iterator(it, graph);
}

template <typename DirectedGraph>
typename adjacent_nodes_iterator<DirectedGraph>::reference adjacent_nodes_iterator<DirectedGraph>::operator*()
{
    return this->m_nodeIterator->get();
}

template <typename DirectedGraph>
typename adjacent_nodes_iterator<DirectedGraph>::pointer adjacent_nodes_iterator<DirectedGraph>::operator->()
{
    return &(this->m_nodeIterator->get());
}

template <typename DirectedGraph>
adjacent_nodes_iterator<DirectedGraph> &adjacent_nodes_iterator<DirectedGraph>::operator++()
{
    this->increment();
    return *this;
}

template <typename DirectedGraph>
adjacent_nodes_iterator<DirectedGraph> &adjacent_nodes_iterator<DirectedGraph>::operator++(int)
{
    auto oldIt = *this;
    this->increment();
    return oldIt;
}

template <typename DirectedGraph>
adjacent_nodes_iterator<DirectedGraph> &adjacent_nodes_iterator<DirectedGraph>::operator--()
{
    this->decrement();
    return *this;
}

template <typename DirectedGraph>
adjacent_nodes_iterator<DirectedGraph> &adjacent_nodes_iterator<DirectedGraph>::operator--(int)
{
    auto oldIt = *this;
    this->decrement();
    return *this;
}
#endif