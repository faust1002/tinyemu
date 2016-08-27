find_package (pcap)
find_package (dpdk)

add_subdirectory (dpdk)
add_subdirectory (unittests)

if (${DPDK_FOUND})
    include_directories (${DPDK_INCLUDE_DIR})
    add_definitions (${DPDK_INCLUDE_CONFIG})
    link_directories (${DPDK_LIBRARY_DIR})
endif ()

if (${LIBPCAP_FOUND})
    include_directories (${PCAP_INCLUDE_DIR})
    link_directories (${PCAP_LIBRARY_DIR})
endif ()

add_executable (${PROJECT_NAME} main.cpp)

if (${DPDK_FOUND})
    target_link_libraries (${PROJECT_NAME} ${DPDK_LIBRARIES})
endif ()

if (${LIBPCAP_FOUND})
    target_link_libraries (${PROJECT_NAME} ${PCAP_LIBRARY})
endif ()

target_link_libraries (${PROJECT_NAME} "dpdk")
target_link_libraries (${PROJECT_NAME} "-lpthread -ldl -lrt")

install (TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_BINARY_DIR}/artifacts")
