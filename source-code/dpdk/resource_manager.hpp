#pragma once

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

private:
    resource_manager();
};

}
