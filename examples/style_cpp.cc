#include <simple_logger/simple_logger.hpp>

using namespace simple_logger;

int main() {
  logger.Debug() << "This message shouldn't be printed!";
  logger.Info() << "Info message: <" << 8888 << '>';
  logger.Warn() << "Warn message: <" << 8888 << '>';
  logger.Error() << "Error message: <" << 8888 << '>';
  return 0;
}
