cmake_minimum_required(VERSION 3.0.0)
project(simple_logger
    VERSION 0.3.1
    LANGUAGES CXX
    DESCRIPTION "A simple, multifunctional and header-only log library for C++17"
    HOMEPAGE_URL "https://github.com/Timothy-Liuxf/simple_logger"
)
set(CMAKE_CXX_STANDARD 17)
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX /utf-8")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")
endif()

include_directories(./include)
include_directories(./third_party/fmt/include)
add_subdirectory(examples)
