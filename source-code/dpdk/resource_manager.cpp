#include "resource_manager.hpp"
#include <utility>

namespace dpdk
{

resource_manager::resource_manager()
{}

resource_manager& create_resource_manager()
{
    static resource_manager rm {};
    return rm;
}

}
