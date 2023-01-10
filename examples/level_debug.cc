// This file is part of simple_logger.
// Copyright (c) 2023, Timothy Liu. All rights reserved.
// License    : MIT License
// Project URL: https://github.com/Timothy-Liuxf/simple_logger

#include <simple_logger/simple_logger.hpp>

using namespace simple_logger;

int main() {
  std::cout << "There should be 4 logs below: " << std::endl;
  logger.Debug("Debug message.");
  logger.Info("Info message.");
  logger.Warn("Warn message.");
  logger.Error("Error message.");
  return 0;
}
