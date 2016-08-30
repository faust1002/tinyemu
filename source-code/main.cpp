#include "logging.hpp"
#include "dpdk.hpp"
#include <iostream>
#include <exception>

int main(int argc, char** argv)
try
{
    std::cerr << "Hello tinyemu!\n";
    std::cerr << "Compilation datetime " << __DATE__ << " " << __TIME__ << '\n';

    dpdk::init_environment(argc, argv);

    helpers::init_logging("zosia.log");

    LOG_TRACE << "kasia 0";
    LOG_DEBUG << "kasia 1";
    LOG_INFO << "kasia 2";
    LOG_WARNING << "kasia 3";
    LOG_ERROR << "kasia 4";
    LOG_FATAL << "kasia 5";

    std::cerr << "Goodbye tinyemu!\n";

    return 0;
}
catch (std::exception& ex)
{
    std::cerr << "Something inherently wrong happen!\n";
    std::cerr << ex.what() << '\n';
    return 100;
}
