#include "resource_manager.hpp"
#include "resource_list.hpp"
#include "lcore_id.hpp"
#include "port.hpp"
#include "queue.hpp"
#include "logging.hpp"
#include "rte_lcore.h"
#include "rte_ethdev.h"

namespace dpdk
{

resource_manager::resource_manager()
{
    auto nb_cores = rte_lcore_count();
    LOG_DEBUG << "Found " << nb_cores << " core(s)";
    lcores = internal::resource_list<dpdk_traits<lcore_id>::id_type> {nb_cores};

    auto nb_ports = rte_eth_dev_count();
    LOG_DEBUG << "Found " << static_cast<unsigned int>(nb_ports) << " ports(s)";
    ports = internal::resource_list<dpdk_traits<port>::id_type> {nb_ports};

    for (auto idx = 0u; idx != nb_ports; ++idx)
    {
        rte_eth_dev_info dev_info = {};
        rte_eth_dev_info_get(idx, &dev_info);
        LOG_DEBUG << "Port " << idx << " has " << dev_info.max_rx_queues << " rx queue(s)"
                  << " and " << dev_info.max_tx_queues  << " tx queue(s)";
        auto nb_queues = std::min(dev_info.max_rx_queues, dev_info.max_tx_queues);
        LOG_DEBUG << nb_queues << "queue(s) will be used";
        queues[idx] = internal::resource_list<dpdk_traits<queue>::id_type>(nb_queues);
    }
}

lcore_id resource_manager::get_lcore()
{
    return lcore_id {lcores.allocate()};
}

port resource_manager::get_port(dpdk_traits<port>::id_type port_id)
{
    return port {ports.allocate(port_id)};
}

queue resource_manager::get_queue(const port& p)
{
    auto id = dpdk_traits<port>::id(p);
    if (queues.size() >= id)
        throw std::logic_error {"Port doesn't exitst"};

    return queue {queues[id].allocate()};
}

resource_manager& create_resource_manager()
{
    static resource_manager rm {};
    return rm;
}

}
