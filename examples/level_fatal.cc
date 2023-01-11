// This file is part of simple_logger.
// Copyright (c) 2023, Timothy Liu. All rights reserved.
// License    : MIT License
// Project URL: https://github.com/Timothy-Liuxf/simple_logger

#include <simple_logger/simple_logger.hpp>

using namespace simple_logger;

int main() {
  std::cout << "There should be 1 log below: " << std::endl;
  logger.Trace("This message shouldn't be printed!");
  logger.Debug("This message shouldn't be printed!");
  logger.Info("This message shouldn't be printed!");
  logger.Warn("This message shouldn't be printed!");
  logger.Error("This message shouldn't be printed!");
  logger.Fatal("Fatal message.");
  return 0;
}
