include_simple_loggerdir = ${includedir}/simple_logger
include_simple_logger_HEADERS =                                                \
    %reldir%/defs.hpp                                                          \
    %reldir%/simple_logger.hpp                                                 \
    ${NOTHING}

include_simple_logger_detailsdir = ${includedir}/simple_logger/details
include_simple_logger_details_HEADERS =                                        \
    %reldir%/details/win32.ipp                                                 \
    %reldir%/details/colorctl.ipp                                              \
    ${NOTHING}
