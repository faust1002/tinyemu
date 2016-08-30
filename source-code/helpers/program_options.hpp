#pragma once

#include <iosfwd>
#include <string>
#include <cstdint>

namespace helpers
{

struct cfg_options
{
    bool help = false;
    std::string log_file = "";
    std::string log_severity = "";
    int log_size = 0;
    uint8_t port_id = 0u;
};

std::ostream& operator<<(std::ostream& os,
                         const cfg_options& cfg);

cfg_options parse(int argc, char**);

std::string get_help();

}
