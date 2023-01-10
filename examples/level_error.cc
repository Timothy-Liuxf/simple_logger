#include <simple_logger/simple_logger.hpp>

using namespace simple_logger;

int main() {
  std::cout << "There should be 1 log below: " << std::endl;
  logger.Debug("This message shouldn't be printed!");
  logger.Info("This message shouldn't be printed!");
  logger.Warn("This message shouldn't be printed!");
  logger.Error("Error message.");
  return 0;
}
