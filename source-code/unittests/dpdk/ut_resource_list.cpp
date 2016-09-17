#include "resource_list.hpp"
#include "gtest/gtest.h"
#include <stdexcept>

using element_type_t = unsigned int;
using namespace dpdk::internal;

TEST(TestResourceList, EmptyList)
{
    resource_list<element_type_t> list;
    ASSERT_TRUE(list.empty());
}

TEST(TestResourceList, ThrowIfListIsEmpty)
{
    dpdk::internal::resource_list<element_type_t> list;
    ASSERT_THROW(list.allocate(), std::logic_error);
}

TEST(TestResourceList, Allocate)
{
    resource_list<element_type_t> list {element_type_t {3}};

    ASSERT_EQ(element_type_t {0}, list.allocate());
    ASSERT_EQ(element_type_t {1}, list.allocate());
    ASSERT_EQ(element_type_t {2}, list.allocate());
}

TEST(TestResourceList, AllocateOutOfRangeElement)
{
    resource_list<element_type_t> list;
    ASSERT_THROW(list.allocate(element_type_t {15}), std::out_of_range);
}

TEST(TestResourceList, AllocatePreviouslyAllocatedElement)
{
    auto nb_elements = element_type_t {42};
    auto element = element_type_t {0};
    resource_list<element_type_t> list {nb_elements};
    list.allocate(element);

    ASSERT_THROW(list.allocate(element), std::logic_error);
}

TEST(TestResourceList, AllocateOutOfOrder)
{
    resource_list<element_type_t> list {element_type_t {4}};

    ASSERT_EQ(element_type_t {0}, list.allocate(element_type_t {0}));
    ASSERT_EQ(element_type_t {2}, list.allocate(element_type_t {2}));
    ASSERT_EQ(element_type_t {1}, list.allocate());
    ASSERT_EQ(element_type_t {3}, list.allocate());
}
