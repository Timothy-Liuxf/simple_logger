#ifndef SIMPLE_LOGGER_DEFS_HPP
#define SIMPLE_LOGGER_DEFS_HPP

#define SIMPLE_LOGGER_NAMESPACE       simple_logger
#define SIMPLE_LOGGER_NAMESPACE_BEGIN namespace SIMPLE_LOGGER_NAMESPACE {
#define SIMPLE_LOGGER_NAMESPACE_END   }

#if defined(_WIN32)
#define SIMPLE_LOGGER_WINDOWS
#elif defined(__unix__)
#define SIMPLE_LOGGER_UNIX
#else
#error "Unsupported platform"
#endif  // OS

#ifndef FMT_HEADER_ONLY
#define FMT_HEADER_ONLY
#endif  // FMT_HEADER_ONLY

#endif  // SIMPLE_LOGGER_DEFS_HPP
