find_package (Threads REQUIRED)

include (ExternalProject)
ExternalProject_Add ("gtest" URL "https://github.com/google/googletest/archive/master.zip" PREFIX "${CMAKE_CURRENT_BINARY_DIR}/gtest" INSTALL_COMMAND "")
ExternalProject_Get_Property ("gtest" source_dir binary_dir)

add_library ("libgtest" IMPORTED STATIC)
set_target_properties ("libgtest" PROPERTIES "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a" "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}")

add_library ("libgmock" IMPORTED STATIC)
set_target_properties ("libgmock" PROPERTIES "IMPORTED_LOCATION" "${binary_dir}/googlemock/googlemock.a" "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}")

include_directories ("${source_dir}/googletest/include")
include_directories ("${source_dir}/googlemock/include")

add_library ("ut_runner" STATIC ut_runner.cpp)

add_subdirectory ("dpdk")
