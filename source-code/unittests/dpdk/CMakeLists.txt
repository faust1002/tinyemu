set (ut_suite_name "ut_dpdk")

set (src
     "ut_dpdk.cpp"
     "ut_resource_list.cpp"
)

add_executable (${ut_suite_name} ${src})

target_link_libraries (${ut_suite_name} "dpdk")
target_link_libraries (${ut_suite_name} "ut_runner")
target_link_libraries (${ut_suite_name} "libgtest")

install (TARGETS ${ut_suite_name} DESTINATION "${CMAKE_BINARY_DIR}/artifacts")
