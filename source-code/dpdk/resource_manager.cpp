#include "resource_manager.hpp"

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
