#pragma once

namespace dpdk
{

template<typename T>
struct dpdk_traits
{
    using id_type = typename T::id_type;

    static
    constexpr id_type id(const T& x)
    {
        return x.id;
    }
};

}
