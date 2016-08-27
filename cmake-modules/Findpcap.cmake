find_program (pcap_config_executable pcap-config)

if (pcap_config_executable)
    execute_process (COMMAND ${pcap_config_executable} ARGS "--cflags" OUTPUT_VARIABLE PCAP_INCLUDE_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process (COMMAND ${pcap_config_executable} ARGS "--libs" OUTPUT_VARIABLE LIBRARIES OUTPUT_STRIP_TRAILING_WHITESPACE)
    separate_arguments (PCAP_LIBRARIES UNIX_COMMAND "${LIBRARIES}")
    list (GET PCAP_LIBRARIES 0 PCAP_LIBRARY_DIR)
    list (GET PCAP_LIBRARIES 1 PCAP_LIBRARY)
    message (STATUS "libpcap include dir: " ${PCAP_INCLUDE_DIR})
    message (STATUS "libpcap library dir: ${PCAP_LIBRARY_DIR}")
    message (STATUS "libpcap library: " ${PCAP_LIBRARY})
else ()
    message ("Unable to find libpcap")
endif ()

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args ("libpcap" DEFAULT_MSG PCAP_INCLUDE_DIR PCAP_LIBRARY_DIR PCAP_LIBRARIES)

mark_as_advanced (PCAP_INCLUDE_DIR PCAP_LIBRARY_DIR PCAP_LIBRARIES)
