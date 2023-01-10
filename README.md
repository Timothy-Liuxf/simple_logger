# simple_logger

![display](./assets/display.png)

## Introduction

`simple_logger`, a simple, multifunctional and header-only log library for C++17.

## Supported Platform

+ Unix-like Operating Systems (Linux, MacOS, FreeBSD, ...)
+ Windows x86/x64 (MSVC, MinGW, MinGW-w64, Cygwin, ...)
+ ...

## Supported Compiler

MSVC, GCC and Clang, etc. supporting **C++17 standard or above**.

## Clone this Repository

Run:

```shell
$ git clone https://github.com/Timothy-Liuxf/simple_logger.git --recursive
```

or

```shell
$ git clone https://github.com/Timothy-Liuxf/simple_logger.git
$ cd simple_logger
$ git submodule update --init --recursive
```

## Get Started

`simple_logger` is a header-only library and needn't to be built. Just add the `include` directory into the *include directory* of your C++ project and include `simple_logger/simple_logger.hpp` to get started.

### Log Levels

There are four log levels in `simple_logger`: `Debug`, `Info`, `Warn` and `Error`. The first two levels will print log messages into `stdout`, while the other two will print into `stderr`. By default, log messages in `Debug` level are **NOT** printed.

### Quick Start

There are three styles to log messages.

#### C++ Style

You can log messages in C++ `iostream` style:

```c++
#include <simple_logger/simple_logger.hpp>

using namespace simple_logger;

int main() {
  logger.Debug() << "This message shouldn't be printed by default!";
  logger.Info() << "Info message: <" << 8888 << '>';
  logger.Warn() << "Warn message: <" << 8888 << '>';
  logger.Error() << "Error message: <" << 8888 << '>';
  return 0;
}
```

#### Function Style

You can also log messages just as a variadic function:

```c++
#include <simple_logger/simple_logger.hpp>

using namespace simple_logger;

int main() {
  logger.Debug() << "This message shouldn't be printed by default!";
  logger.Info("Info message: <", 8888, '>');
  logger.Warn("Warn message: <", 8888, '>');
  logger.Error("Error message: <", 8888, '>');
  return 0;
}
```

#### format style

You can also log messages in C++20 format library style:

```c++
#include <simple_logger/simple_logger.hpp>

using namespace simple_logger;

int main() {
  logger.Debugf("This message shouldn't be printed by default!!");
  logger.Infof("Info message: <{}>", 8888);
  logger.Warnf("Warn message: <{}>", 8888);
  logger.Errorf("Error message: <{}>", 8888);
  return 0;
}
```

### Format multiple objects

With [fmtlib](https://github.com/fmtlib/fmt), `simple_logger` can support almost all formatting methods in fmtlib. Such as:

1. Format ranges:

   ```c++
   #include <simple_logger/simple_logger.hpp>
   
   #include <fmt/ranges.h>
   #include <array>
   
   using namespace simple_logger;
   
   int main() {
     std::array arr {0, 1, 2, 3};
     logger.Infof("Info message: {}: {}", arr, arr.size());
     return 0;
   }
   ```

2. Format time:

   ```c++
   #include <simple_logger/simple_logger.hpp>
   
   #include <fmt/chrono.h>
   #include <chrono>
   
   using namespace simple_logger;
   
   int main() {
     auto current_time = fmt::localtime(
         std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
     logger.Infof("Info message: current_time: {:%Y-%m-%d %H:%M:%S}",
                  current_time);
     return 0;
   }
   ```

3. F

   ```c++
   #include <simple_logger/simple_logger.hpp>
   
   #include <fmt/format.h>
   
   using namespace simple_logger;
   
   int main() {
     using fmt::literals::operator""_a;
     logger.Infof("Info message: {num}", "num"_a = 5);
     return 0;
   }
   ```

4. For more usage, please see [fmtlib API documentation](https://fmt.dev/latest/api.html).

## Build Examples

Source code of the examples are in the `examples` directory.

To build the examples, run:

```shell
$ mkdir build
$ cd build
$ cmake ..
$ make -j$(nproc)
```

To run the examples, then run:

```shell
$ ./examples/<example_name>
```

The `<example_name>` is the same as the name of the corresponding source file after removing the extension name `.cc`.

## Author

Copyright (C) 2023, [Timothy Liu](https://github.com/Timothy-Liuxf)

All rights reserved

## LICENSE

[MIT License](https://github.com/Timothy-Liuxf/simple_logger/blob/master/LICENSE.txt)