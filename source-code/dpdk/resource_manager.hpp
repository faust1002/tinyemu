#pragma once
#include "resource_list.hpp"
#include "dpdk_traits.hpp"
#include "lcore_id.hpp"
#include "port.hpp"
#include <unordered_map>

namespace dpdk
{

class resource_manager;

resource_manager& create_resource_manager();

class resource_manager
{
public:
    friend resource_manager& create_resource_manager();
    resource_manager(const resource_manager&) = delete;
    resource_manager(resource_manager&&) = default;

    resource_manager& operator=(const resource_manager&) = delete;
    resource_manager& operator=(resource_manager&&) = default;

    ~resource_manager() = default;

    lcore_id get_lcore();
    port get_port(dpdk_traits<port>::id_type port_id);
    queue get_queue(const port& port);

private:
    resource_manager();

    internal::resource_list<dpdk_traits<lcore_id>::id_type> lcores;
    internal::resource_list<dpdk_traits<port>::id_type> ports;
    std::unordered_map<dpdk_traits<port>::id_type,
                       internal::resource_list<dpdk_traits<queue>::id_type>> queues;
};

}
