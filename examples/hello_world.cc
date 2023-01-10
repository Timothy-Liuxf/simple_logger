#include <simple_logger/simple_logger.hpp>

#include <fmt/chrono.h>
#include <fmt/ranges.h>

#include <chrono>
#include <vector>

using namespace simple_logger;

int main() {
  logger.Info() << "This is C++ style: ";
  logger.Info() << "Info message: "
                << "Hello, world " << 2023 << '!';
  logger.Warn() << "Warn message: "
                << "Hello, world " << 2023 << '!';
  logger.Error() << "Warn message: "
                 << "Hello, world " << 2023 << '!';
  logger.Debug() << "Debug message is not printed by default!";

  logger.Info() << "This is function style: ";
  logger.Info("Info message: ", "Hello, world ", 2023, '!');
  logger.Warn("Warn message: ", "Hello, world ", 2023, '!');
  logger.Error("Error message: ", "Hello, world ", 2023, '!');

  logger.Info() << "This is format style: ";
  logger.Infof("Info message: {} {}!", "Hello, world ", 2023);

  logger.Info() << "We can also format ranges (requires fmt/ranges.h): ";
  logger.Warnf("Warn message: {}", std::vector<int> {0, 1, 2, 3});

  logger.Info() << "We can also format time (requires fmt/chrono.h): ";
  logger.Errorf("Error message: {:%Y-%m-%d %H:%M:%S}",
                fmt::localtime(std::chrono::system_clock::to_time_t(
                    std::chrono::system_clock::now())));
  return 0;
}
