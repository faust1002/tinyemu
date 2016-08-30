#include "program_options.hpp"
#include <iostream>
#include <string>
#include <cstdint>
#include "boost/program_options/options_description.hpp"
#include "boost/program_options/variables_map.hpp"
#include "boost/program_options/parsers.hpp"

namespace helpers
{

std::ostream& operator<<(std::ostream& os, const cfg_options& cfg)
{
    os << "help = " << cfg.help
       << ", log_file = " << cfg.logging.log_file
       << ", log_severity = " << cfg.logging.log_severity
       << ", log_size = " << cfg.logging.log_size
       << ", port_id = " << cfg.network.port_id;
    return os;
}

cfg_options parse(int argc, char** argv)
{
    namespace po = boost::program_options;

    cfg_options options;

    po::options_description op {"Allowed options"};
    op.add_options()
        ("help", po::value<bool>(&options.help)->default_value(false))
        ("logfile,l", po::value<std::string>(&options.logging.log_file)->default_value("stdout"))
        ("severity,s", po::value<std::string>(&options.logging.log_severity)->default_value("info"))
        ("max,m", po::value<int>(&options.logging.log_size)->default_value(15))
        ("port_id,p", po::value<uint8_t>(&options.network.port_id)->required())
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, op), vm);
    po::notify(vm);

    return options;
}

std::string get_help()
{
    return std::string {};
}

}
