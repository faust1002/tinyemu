#pragma once
#include <stdexcept>
#include <type_traits>
#include <vector>
#include "boost/optional.hpp"

namespace dpdk
{

namespace internal
{

template<typename T = unsigned int>
class resource_list
{
public:
    resource_list(T elements = T {0})
    {
        static_assert(std::is_unsigned<T>::value, "T has to be unsigned");

        if (elements == T {0}) return;
        else if (elements == T {1}) create_single_element_list();
        else create_list(elements);

        first_free_node_idx = size_type {0};
    }

    T allocate()
    {
        if (empty())
            throw std::logic_error {"Resource list is empty"};

        auto idx = *first_free_node_idx;
        T v = list[idx].value;
        list[idx].available = false;
        first_free_node_idx = list[idx].next;

        return v;
    }

    T allocate(T element)
    {
        if (element >= list.size())
            throw std::out_of_range {"Element out of scope"};

        auto idx = size_type {element};
        if (not list[idx].available)
            throw std::logic_error {"Element has been allocated"};

        auto v = list[idx].value;
        list[idx].available = false;
        if (*first_free_node_idx == idx)
            first_free_node_idx = list[idx].next;
        else
            list[idx - 1].next = list[idx].next;

        return v;
    }

    bool empty() const
    {
        return first_free_node_idx == boost::none;
    }

private:
    void create_single_element_list()
    {
        node_t n {T {0}, boost::none, true};
        list.push_back(n);
    }

    void create_list(T elements)
    {
        list.reserve(elements);

        create_single_element_list();

        T idx = T {1u};
        T last = elements - 1u;
        while (idx != last)
        {
            node_t n {idx, size_type {idx + 1u}, true};
            list.push_back(n);
            ++idx;
        }

        node_t n {last, boost::none, true};
        list.push_back(n);

        list[size_type {0}].next = size_type {1u};
        list[size_type {last}].next = boost::none;
    }


    struct node_t;
    using list_t = std::vector<node_t>;
    using size_type = typename list_t::size_type;
    using list_idx_t = boost::optional<size_type>;
    struct node_t
    {
        T value = T {0};
        list_idx_t next = boost::none;
        bool available = false;
    };

    list_t list;
    list_idx_t first_free_node_idx = boost::none;
};

}

}
