#include <simple_logger/simple_logger.hpp>

using namespace simple_logger;

int main() {
  std::cout << "There should be 3 logs below: " << std::endl;
  logger.Debug("This message shouldn't be printed!");
  logger.Info("Info message.");
  logger.Warn("Warn message.");
  logger.Error("Error message.");
  return 0;
}
