#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([simple_logger], [0.2.2.0], [liuxf19@163.com], [simple_logger],      dnl
    [https://github.com/Timothy-Liuxf/simple_logger])
AC_CONFIG_SRCDIR([include/simple_logger/simple_logger.hpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([third_party/autoconf-archive/m4])

AM_INIT_AUTOMAKE([foreign subdir-objects])

AX_CXX_COMPILE_STDCXX_17([noext], [mandatory])
CXXFLAGS=""
AX_APPEND_COMPILE_FLAGS([-Wall -Wpedantic -Wextra -Werror], [CXXFLAGS])
AX_APPEND_COMPILE_FLAGS([                                                    dnl
    -Iinclude                                                                dnl
    -Ithird_party/fmt/include                                                dnl
], [CXXFLAGS])

# Whether to build test examples
AM_CONDITIONAL([BUILD_TEST_EXAMPLES], [test "x$BUILD_TEST_EXAMPLES" = "x1"])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CPP
AC_PROG_MAKE_SET

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h stdint.h strings.h sys/param.h sys/socket.h sys/time.h sys/timeb.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_STRUCT_TIMEZONE
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_FUNC_MMAP
AC_FUNC_STRTOD
AC_CHECK_FUNCS([dup2 fchdir floor getcwd getpagesize localtime_r memchr memset mkdir munmap pow regcomp rmdir socket sqrt strcasecmp strchr strdup strerror strrchr strstr strtol strtoull])

AC_CONFIG_FILES([Makefile])

# AC_CONFIG_SUBDIRS([third_party/autoconf-archive])
AC_OUTPUT
