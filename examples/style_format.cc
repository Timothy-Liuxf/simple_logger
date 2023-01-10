// This file is part of simple_logger.
// Copyright (c) 2023, Timothy Liu. All rights reserved.
// License    : MIT License
// Project URL: https://github.com/Timothy-Liuxf/simple_logger

#include <simple_logger/simple_logger.hpp>

// Formatting `array` requires `fmt/ranges.h` to be included
#include <fmt/ranges.h>

#include <fmt/chrono.h>

#include <array>
#include <chrono>

using namespace simple_logger;

int main() {
  std::array arr {0, 1, 2, 3};
  logger.Debugf("This message shouldn't be printed!");
  logger.Infof("Info message: {}: {}", arr, arr.size());
  logger.Warnf("Warn message: {}: {}", arr, arr.size());
  logger.Errorf("Error message: {}: {}", arr, arr.size());

  auto current_time = fmt::localtime(
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
  logger.Debugf("This message shouldn't be printed!");
  logger.Infof("Info message: current_time: {:%Y-%m-%d %H:%M:%S}",
               current_time);
  logger.Warnf("Warn message: current_time: {:%Y-%m-%d %H:%M:%S}",
               current_time);
  logger.Errorf("Error message: current_time: {:%Y-%m-%d %H:%M:%S}",
                current_time);
  return 0;
}
