#include "logging.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "boost/log/core.hpp"
#include "boost/log/trivial.hpp"
#include "boost/log/expressions.hpp"
#include "boost/log/sinks/text_file_backend.hpp"
#include "boost/log/utility/setup/file.hpp"
#include "boost/log/utility/setup/common_attributes.hpp"
#include "boost/log/sources/severity_logger.hpp"
#include "boost/log/sources/record_ostream.hpp"
#include "boost/log/support/date_time.hpp"

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

}

namespace helpers
{

void init_logging(const std::string& filename)
{
    auto fn = prepare_filename(filename);
    boost::log::add_file_log(
        boost::log::keywords::file_name = fn.c_str(),
        boost::log::keywords::rotation_size = 10 * 1024 * 1024,
        boost::log::keywords::format =
        (
            boost::log::expressions::stream
                << boost::log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
                << ": [" << boost::log::trivial::severity
                << "] " << boost::log::expressions::smessage
        )
    );

    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::trace
    );

    boost::log::add_common_attributes();
}

}
