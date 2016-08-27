#include "dpdk.hpp"
#include <stdexcept>
#include "rte_eal.h"

namespace dpdk
{

int init_environment(int argc, char** argv)
{
    auto result = rte_eal_init(argc, argv);
    if (result < 0)
    {
        throw std::runtime_error {"Unable to init environment"};
    }
    return result;
}

}
