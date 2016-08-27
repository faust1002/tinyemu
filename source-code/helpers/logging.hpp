#pragma once

#include <string>
#include <cstring>

#define BOOST_LOG_DYN_LINK

#include "boost/log/core.hpp"
#include "boost/log/trivial.hpp"

#define FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOG_TRACE BOOST_LOG_TRIVIAL(trace) << FILENAME << ":" << __LINE__ << " "
#define LOG_DEBUG BOOST_LOG_TRIVIAL(debug) << FILENAME << ":" << __LINE__ << " "
#define LOG_INFO BOOST_LOG_TRIVIAL(info) << FILENAME << ":" << __LINE__ << " "
#define LOG_WARNING BOOST_LOG_TRIVIAL(warning) << FILENAME << ":" << __LINE__ << " "
#define LOG_ERROR BOOST_LOG_TRIVIAL(error) << FILENAME << ":" << __LINE__ << " "
#define LOG_FATAL BOOST_LOG_TRIVIAL(fatal) << FILENAME << ":" << __LINE__ << " "

namespace helpers
{

void init_logging(const std::string& filename);

}
