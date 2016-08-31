set (LIB_NAME "helpers")
add_library (${LIB_NAME} STATIC logging.cpp program_options.cpp)

if (Boost_FOUND)
    target_include_directories (${LIB_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
endif ()

target_include_directories (${LIB_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
