cmake_minimum_required(VERSION 3.0.0)
project(simple_logger)
set(CMAKE_CXX_STANDARD 17)

include_directories(./include)
include_directories(./third_party/fmt/include)
add_subdirectory(examples)
