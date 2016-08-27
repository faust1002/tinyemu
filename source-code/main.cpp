#include "dpdk.hpp"
#include <iostream>
#include <exception>

int main(int argc, char** argv)
try
{
    std::cout << "Hello tinyemu!\n";

    argc = dpdk::init_environment(argc, argv);

    return 0;
}
catch (std::exception& ex)
{
    std::cerr << "Something inherently wrong happen!\n";
    std::cerr << ex.what() << '\n';
    return 100;
}
