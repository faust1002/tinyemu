find_package (Boost 1.58 COMPONENTS log date_time program_options)
if (Boost_FOUND)
    include_directories (${Boost_INCLUDE_DIRS})
endif ()

add_library ("helpers" STATIC logging.cpp program_options.cpp)
target_include_directories ("helpers" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
