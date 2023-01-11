// This file is part of simple_logger.
// Copyright (c) 2023, Timothy Liu. All rights reserved.
// License    : MIT License
// Project URL: https://github.com/Timothy-Liuxf/simple_logger

#include <simple_logger/simple_logger.hpp>

#include <memory>
#include <thread>
#include <utility>
#include <vector>

constexpr std::size_t nthreads = 128;

using namespace simple_logger;

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  // Thread-safe
  std::vector<std::unique_ptr<std::thread>> threads(nthreads);
  for (std::size_t i = 0; i < nthreads; ++i) {
    threads[i] = std::make_unique<std::thread>([i, argc] {
      std::this_thread::yield();
      logger.Info() << "Thread-safe "
                    << "log. "
                    << "[argc: " << argc << "] "
                    << "At "
                    << "Index: " << i << ".";
    });
  }
  for (std::size_t i = 0; i < nthreads; ++i) {
    threads[i]->join();
    threads[i].reset();
  }

  // Thread-unsafe
  for (std::size_t i = 0; i < nthreads; ++i) {
    threads[i] = std::make_unique<std::thread>([i, argc] {
      std::this_thread::yield();
      uslogger.Info() << "Thread-unsafe "
                      << "log. "
                      << "[argc: " << argc << "] "
                      << "At "
                      << "Index: " << i << ".";
    });
  }
  for (std::size_t i = 0; i < nthreads; ++i) {
    threads[i]->join();
    threads[i].reset();
  }
  return 0;
}
