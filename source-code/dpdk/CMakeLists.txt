find_package (pcap)
find_package (dpdk)

if (${DPDK_FOUND})
    include_directories (${DPDK_INCLUDE_DIR})
    add_definitions (${DPDK_INCLUDE_CONFIG})
endif ()

if (${LIBPCAP_FOUND})
    include_directories (${PCAP_INCLUDE_DIR})
endif ()

add_library ("dpdk" STATIC dpdk.cpp resource_manager.cpp)
target_include_directories ("dpdk" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
