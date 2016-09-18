#pragma once
#include <vector>
#include <cstdint>
#include "queue.hpp"

namespace dpdk
{

struct port
{
    using id_type = uint8_t;

    id_type id = 0u;
    std::vector<queue> queues = {};
};

}
