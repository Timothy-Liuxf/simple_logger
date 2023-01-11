// This file is part of simple_logger.
// Copyright (c) 2023, Timothy Liu. All rights reserved.
// License    : MIT License
// Project URL: https://github.com/Timothy-Liuxf/simple_logger

#ifndef SIMPLE_LOGGER_HPP_
#define SIMPLE_LOGGER_HPP_

#include <simple_logger/defs.hpp>

#include <cstdint>
#include <functional>
#include <iostream>
#include <string_view>
#include <utility>

#include <fmt/chrono.h>

#define SIMPLE_LOGGER_LOG_NONE  0
#define SIMPLE_LOGGER_LOG_ERROR 1
#define SIMPLE_LOGGER_LOG_WARN  2
#define SIMPLE_LOGGER_LOG_INFO  3
#define SIMPLE_LOGGER_LOG_DEBUG 4

#if defined(SIMPLE_LOGGER_DISABLE_LOG)
#define SIMPLE_LOGGER_LOG_LEVEL SIMPLE_LOGGER_LOG_NONE
#elif defined(SIMPLE_LOGGER_ENABLE_LOG_DEBUG)
#define SIMPLE_LOGGER_LOG_LEVEL SIMPLE_LOGGER_LOG_DEBUG
#elif defined(SIMPLE_LOGGER_ENABLE_LOG_INFO)
#define SIMPLE_LOGGER_LOG_LEVEL SIMPLE_LOGGER_LOG_INFO
#elif defined(SIMPLE_LOGGER_ENABLE_LOG_WARN)
#define SIMPLE_LOGGER_LOG_LEVEL SIMPLE_LOGGER_LOG_WARN
#elif defined(SIMPLE_LOGGER_ENABLE_LOG_ERROR)
#define SIMPLE_LOGGER_LOG_LEVEL SIMPLE_LOGGER_LOG_ERROR
#else
#define SIMPLE_LOGGER_LOG_LEVEL SIMPLE_LOGGER_LOG_INFO
#endif

SIMPLE_LOGGER_NAMESPACE_BEGIN

namespace details {

#include "details/colorctl.ipp"

using namespace std::literals::string_view_literals;
static constexpr std::string_view kDebugPrompt = "debug"sv;
static constexpr std::string_view kInfoPrompt  = "info"sv;
static constexpr std::string_view kWarnPrompt  = "warn"sv;
static constexpr std::string_view kErrorPrompt = "error"sv;

}  // namespace details

class Logger {
 public:
  class LogHelper {
   private:
    LogHelper(std::ostream& os, const std::function<void()>& postfix)
        : os_(os), postfix_(postfix) {}
    LogHelper(const LogHelper&)            = delete;
    LogHelper(LogHelper&&)                 = delete;
    LogHelper& operator=(const LogHelper&) = delete;
    LogHelper& operator=(LogHelper&&)      = delete;

   public:
    ~LogHelper() noexcept(false) {
      this->postfix_();
      this->os_ << std::endl;
    }

   public:
    template <typename Val>
    LogHelper& operator<<(Val&& val) {
      this->os_ << std::forward<Val>(val);
      return *this;
    }

    LogHelper& operator<<(std::ostream& (*func)(std::ostream&)) {
      this->os_ << func;
      return *this;
    }

   private:
    std::ostream&         os_;
    std::function<void()> postfix_;

    friend class Logger;
  };

  class EmptyLogHelper {
   public:
    template <typename Val>
    EmptyLogHelper& operator<<(Val&&) {
      return *this;
    }

    EmptyLogHelper& operator<<(std::ostream& (*)(std::ostream&)) {
      return *this;
    }
  };

 public:
  auto Debug() {
#if SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_DEBUG
    return this->StdoutLog(details::kBeginGreen, details::kDebugPrompt);
#else
    return EmptyLogHelper();
#endif  // SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_DEBUG
  }

  template <typename... Vals>
  void Debug(Vals&&... vals) {
    (this->Debug() << ... << std::forward<Vals>(vals));
  }

  template <typename Format, typename... Args>
  void Debugf(Format&& fmt, Args&&... args) {
    this->Debug() << fmt::format(std::forward<Format>(fmt),
                                 std::forward<Args>(args)...);
  }

  auto Info() {
#if SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_INFO
    Logger::PrintTime(std::cout);
    std::cout << '[' << details::kInfoPrompt << "] ";
    return LogHelper(std::cout, [] {});
#else
    return EmptyLogHelper();
#endif  // SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_INFO
  }

  template <typename... Vals>
  void Info(Vals&&... vals) {
    (this->Info() << ... << std::forward<Vals>(vals));
  }

  template <typename Format, typename... Args>
  void Infof(Format&& fmt, Args&&... args) {
    this->Info() << fmt::format(std::forward<Format>(fmt),
                                std::forward<Args>(args)...);
  }

  auto Warn() {
#if SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_WARN
    return this->StderrLog(details::kBeginYellow, details::kWarnPrompt);
#else
    return EmptyLogHelper();
#endif  // SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_WARN
  }

  template <typename... Vals>
  void Warn(Vals&&... vals) {
    (this->Warn() << ... << std::forward<Vals>(vals));
  }

  template <typename Format, typename... Args>
  void Warnf(Format&& fmt, Args&&... args) {
    this->Warn() << fmt::format(std::forward<Format>(fmt),
                                std::forward<Args>(args)...);
  }

  auto Error() {
#if SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_ERROR
    return this->StderrLog(details::kBeginRed, details::kErrorPrompt);
#else
    return EmptyLogHelper();
#endif  // SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_ERROR
  }

  template <typename... Vals>
  void Error(Vals&&... vals) {
    (this->Error() << ... << std::forward<Vals>(vals));
  }

  template <typename Format, typename... Args>
  void Errorf(Format&& fmt, Args&&... args) {
    this->Error() << fmt::format(std::forward<Format>(fmt),
                                 std::forward<Args>(args)...);
  }

 private:
  void PrintTime(std::ostream& os) {
    os << fmt::format("{:%Y-%m-%d %H:%M:%S} ",
                      fmt::localtime(std::chrono::system_clock::to_time_t(
                          std::chrono::system_clock::now())));
  }

  LogHelper StdoutLog(details::ColorCtlType token, std::string_view level) {
    auto end_token = details::GetOutputEndColorToken();
    details::SetOutputColor(token);
    Logger::PrintTime(std::cout);
    std::cout << '[' << level << "] ";
    return LogHelper(std::cout, [=] { details::SetOutputColor(end_token); });
  }

  LogHelper StderrLog(details::ColorCtlType token, std::string_view level) {
    auto end_token = details::GetErrorEndColorToken();
    details::SetErrorColor(token);
    Logger::PrintTime(std::cerr);
    std::cerr << '[' << level << "] ";
    return LogHelper(std::cerr, [=] { details::SetErrorColor(end_token); });
  }
};

inline Logger logger;

SIMPLE_LOGGER_NAMESPACE_END

#endif  // SIMPLE_LOGGER_HPP_
