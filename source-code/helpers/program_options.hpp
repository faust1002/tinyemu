#pragma once

#include <iosfwd>
#include <string>
#include <cstdint>

namespace helpers
{

struct cfg_logging
{
    std::string log_file = "";
    std::string log_severity = "";
    int log_size = 0;
};

struct cfg_network
{
    uint8_t port_id;
};

struct cfg_options
{
    bool help = false;
    cfg_logging logging;
    cfg_network network;
};

std::ostream& operator<<(std::ostream& os,
                         const cfg_options& cfg);

cfg_options parse(int argc, char**);

std::string get_help();

}
