find_package (dpdk)
find_package (pcap)
find_package (Boost 1.58 COMPONENTS system log program_options)

add_subdirectory (dpdk)
add_subdirectory (helpers)
add_subdirectory (unittests)

if (${DPDK_FOUND})
    link_directories (${DPDK_LIBRARY_DIR})
endif ()

if (${LIBPCAP_FOUND})
    link_directories (${PCAP_LIBRARY_DIR})
endif ()

if (${Boost_FOUND})
    link_directories (${Boost_LIBRARY_DIR})
endif ()

add_executable (${PROJECT_NAME} main.cpp)

if (${DPDK_FOUND})
    target_link_libraries (${PROJECT_NAME} ${DPDK_LIBRARIES})
endif ()

if (${LIBPCAP_FOUND})
    target_link_libraries (${PROJECT_NAME} ${PCAP_LIBRARY})
endif ()

if (${Boost_FOUND})
    target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES})
endif ()

target_link_libraries (${PROJECT_NAME} "dpdk")
target_link_libraries (${PROJECT_NAME} "helpers")
target_link_libraries (${PROJECT_NAME} "-lpthread -ldl -lrt")

install (TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_BINARY_DIR}/artifacts")
