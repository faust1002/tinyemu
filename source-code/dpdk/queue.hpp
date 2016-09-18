#pragma once
#include <cstdint>

namespace dpdk
{

struct queue
{
    using id_type = uint16_t;

    id_type id = 0u;
};

}
