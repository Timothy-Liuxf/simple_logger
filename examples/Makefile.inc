noinst_PROGRAMS += build/examples/hello_world
build_examples_hello_world_SOURCES = %reldir%/hello_world.cc

noinst_PROGRAMS += build/examples/style_cpp
build_examples_style_cpp_SOURCES = %reldir%/style_cpp.cc

noinst_PROGRAMS += build/examples/style_function
build_examples_style_function_SOURCES = %reldir%/style_function.cc

noinst_PROGRAMS += build/examples/style_format
build_examples_style_format_SOURCES = %reldir%/style_format.cc

noinst_PROGRAMS += build/examples/thread_safety
build_examples_thread_safety_SOURCES = %reldir%/thread_safety.cc

noinst_PROGRAMS += build/examples/level_default
build_examples_level_default_SOURCES = %reldir%/level_default.cc

noinst_PROGRAMS += build/examples/level_disable
build_examples_level_disable_SOURCES = %reldir%/level_disable.cc
build_examples_level_disable_CXXFLAGS = -DSIMPLE_LOGGER_DISABLE_LOG

noinst_PROGRAMS += build/examples/level_trace
build_examples_level_trace_SOURCES = %reldir%/level_trace.cc
build_examples_level_trace_CXXFLAGS = -DSIMPLE_LOGGER_ENABLE_LOG_TRACE

noinst_PROGRAMS += build/examples/level_debug
build_examples_level_debug_SOURCES = %reldir%/level_debug.cc
build_examples_level_debug_CXXFLAGS = -DSIMPLE_LOGGER_ENABLE_LOG_DEBUG

noinst_PROGRAMS += build/examples/level_info
build_examples_level_info_SOURCES = %reldir%/level_info.cc
build_examples_level_info_CXXFLAGS = -DSIMPLE_LOGGER_ENABLE_LOG_INFO

noinst_PROGRAMS += build/examples/level_warn
build_examples_level_warn_SOURCES = %reldir%/level_warn.cc
build_examples_level_warn_CXXFLAGS = -DSIMPLE_LOGGER_ENABLE_LOG_WARN

noinst_PROGRAMS += build/examples/level_error
build_examples_level_error_SOURCES = %reldir%/level_error.cc
build_examples_level_error_CXXFLAGS = -DSIMPLE_LOGGER_ENABLE_LOG_ERROR

noinst_PROGRAMS += build/examples/level_fatal
build_examples_level_fatal_SOURCES = %reldir%/level_fatal.cc
build_examples_level_fatal_CXXFLAGS = -DSIMPLE_LOGGER_ENABLE_LOG_FATAL
