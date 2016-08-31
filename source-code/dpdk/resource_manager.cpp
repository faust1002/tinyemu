#include "resource_manager.hpp"
#include "logging.hpp"
#include "rte_lcore.h"
#include "rte_ethdev.h"

namespace dpdk
{

resource_manager::resource_manager()
{
    auto nb_cores = rte_lcore_count();
    LOG_DEBUG << "Found " << nb_cores << " core(s)";
    auto nb_ports = rte_eth_dev_count();
    LOG_DEBUG << "Found " << static_cast<unsigned int>(nb_ports) << " ports(s)";
    for (auto idx = 0u; idx != nb_ports; ++idx)
    {
        rte_eth_dev_info dev_info = {};
        rte_eth_dev_info_get(idx, &dev_info);
        LOG_DEBUG << "Port " << idx << " has " << dev_info.max_rx_queues << " rx queue(s)"
                  << " and " << dev_info.max_tx_queues  << " tx queue(s)";
    }
}

resource_manager& create_resource_manager()
{
    static resource_manager rm {};
    return rm;
}

}
