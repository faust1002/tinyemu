#include "logging.hpp"
#include "program_options.hpp"
#include "dpdk.hpp"
#include "resource_manager.hpp"
#include <iostream>
#include <exception>

int main(int argc, char** argv)
try
{
    std::cerr << "Hello tinyemu!\n";
    std::cerr << "Compilation datetime " << __DATE__ << " " << __TIME__ << '\n';

    dpdk::init_environment(argc, argv);

    auto cfg = helpers::parse(argc, argv);
    if (cfg.help)
    {
        std::cout << helpers::get_help() << '\n';
        return 0;
    }

    helpers::init_logging(cfg.logging);

    dpdk::create_resource_manager();

    std::cerr << "Goodbye tinyemu!\n";

    return 0;
}
catch (std::exception& ex)
{
    std::cerr << "Something inherently wrong happen!\n";
    std::cerr << ex.what() << '\n';
    return 100;
}
