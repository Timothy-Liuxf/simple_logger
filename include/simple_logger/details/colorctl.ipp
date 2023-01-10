#ifndef SIMPLE_LOGGER_HPP_
#error                                                                         \
    "This file should not be included directly. Include simple_logger.hpp instead."
#endif  // SIMPLE_LOGGER_HPP_

#if defined(SIMPLE_LOGGER_WINDOWS)

namespace win32 {

#include "win32.ipp"

}  // namespace win32

using ColorCtlType                               = win32::WORD;
static constexpr inline ColorCtlType kBeginRed   = FOREGROUND_RED;
static constexpr inline ColorCtlType kBeginGreen = FOREGROUND_GREEN;
static constexpr inline ColorCtlType kBeginBlue  = FOREGROUND_BLUE;
static constexpr inline ColorCtlType kBeginYellow =
    FOREGROUND_RED | FOREGROUND_GREEN;

inline ColorCtlType GetOutputEndColorToken() noexcept {
  win32::CONSOLE_SCREEN_BUFFER_INFO csbi;
  win32::GetConsoleScreenBufferInfo(
      win32::GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  return csbi.wAttributes;
}

inline ColorCtlType GetErrorEndColorToken() noexcept {
  win32::CONSOLE_SCREEN_BUFFER_INFO csbi;
  win32::GetConsoleScreenBufferInfo(
      win32::GetStdHandle(STD_ERROR_HANDLE), &csbi);
  return csbi.wAttributes;
}

inline void SetOutputColor(ColorCtlType token) {
  win32::SetConsoleTextAttribute(win32::GetStdHandle(STD_OUTPUT_HANDLE),
                                 token);
}

inline void SetErrorColor(ColorCtlType token) {
  win32::SetConsoleTextAttribute(win32::GetStdHandle(STD_ERROR_HANDLE),
                                 token);
}

#elif defined(SIMPLE_LOGGER_UNIX)

using namespace std::literals::string_view_literals;

using ColorCtlType                                = std::string_view;
static constexpr inline ColorCtlType kBeginRed    = "\033[31m"sv;
static constexpr inline ColorCtlType kBeginGreen  = "\033[32m"sv;
static constexpr inline ColorCtlType kBeginBlue   = "\033[34m"sv;
static constexpr inline ColorCtlType kBeginYellow = "\033[33m"sv;

inline ColorCtlType GetOutputEndColorToken() noexcept { return "\033[0m"sv; }
inline ColorCtlType GetErrorEndColorToken() noexcept { return "\033[0m"sv; }

inline void         SetOutputColor(ColorCtlType token) { std::cout << token; }
inline void         SetErrorColor(ColorCtlType token) { std::cerr << token; }

#endif  // OS
