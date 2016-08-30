#include "logging.hpp"
#include "program_options.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "boost/log/core.hpp"
#include "boost/log/trivial.hpp"
#include "boost/log/expressions.hpp"
#include "boost/log/sinks/text_file_backend.hpp"
#include "boost/log/utility/setup/console.hpp"
#include "boost/log/utility/setup/file.hpp"
#include "boost/log/utility/setup/common_attributes.hpp"
#include "boost/log/sources/severity_logger.hpp"
#include "boost/log/sources/record_ostream.hpp"
#include "boost/log/support/date_time.hpp"

using namespace boost;

namespace
{

std::string prepare_filename(std::string fn)
{
    auto idx = fn.find_last_of('.');
    if (idx == std::string::npos)
    {
        fn += "_%N";
    }
    else
    {
        fn.insert(idx, "_%N");
    }
    return fn;
}

log::trivial::severity_level parse_severity_level(const std::string& severity)
{
    if (severity == "trace")
    {
        return log::trivial::trace;
    }
    else if (severity == "debug")
    {
        return log::trivial::debug;
    }
    else if (severity == "info")
    {
        return log::trivial::info;
    }
    else if (severity == "warn")
    {
        return log::trivial::warning;
    }
    else if (severity == "error")
    {
        return log::trivial::error;
    }
    else if (severity == "fatal")
    {
        return log::trivial::fatal;
    }
    else
    {
        return log::trivial::info;
    }
}

}

namespace helpers
{

void init_logging(const helpers::cfg_logging& cfg)
{
    namespace keywords = log::keywords;
    namespace expressions = log::expressions;

    auto date_formatter = expressions::format_date_time<posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f");
    auto formatter = expressions::stream
                        << date_formatter
                        << ": [" << log::trivial::severity
                        << "] " << log::expressions::smessage;

    if (cfg.log_file == "stdout" || cfg.log_file == "-")
    {
        log::add_console_log()->set_formatter(formatter);
    }
    else
    {
        auto fn = prepare_filename(cfg.log_file);
        log::add_file_log(
            keywords::file_name = fn.c_str(),
            keywords::rotation_size = cfg.log_size * 1024 * 1024,
            keywords::format = formatter
        );
    }

    auto severity = parse_severity_level(cfg.log_severity);
    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= severity
    );

    boost::log::add_common_attributes();
}

}
