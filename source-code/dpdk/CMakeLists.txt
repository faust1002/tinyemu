set (LIB_NAME "dpdk")
add_library (${LIB_NAME} STATIC dpdk.cpp resource_manager.cpp)

if (${DPDK_FOUND})
    target_include_directories (${LIB_NAME} PRIVATE ${DPDK_INCLUDE_DIR})
    add_definitions (${DPDK_INCLUDE_CONFIG})
endif ()

if (${LIBPCAP_FOUND})
    target_include_directories (${LIB_NAME} PRIVATE ${PCAP_INCLUDE_DIR})
endif ()

target_include_directories (${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
