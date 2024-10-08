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
#include <mutex>
#include <string_view>
#include <utility>

#include <fmt/chrono.h>

#define SIMPLE_LOGGER_LOG_NONE_LEVEL  0
#define SIMPLE_LOGGER_LOG_FATAL_LEVEL 1
#define SIMPLE_LOGGER_LOG_ERROR_LEVEL 2
#define SIMPLE_LOGGER_LOG_WARN_LEVEL  3
#define SIMPLE_LOGGER_LOG_INFO_LEVEL  4
#define SIMPLE_LOGGER_LOG_DEBUG_LEVEL 5
#define SIMPLE_LOGGER_LOG_TRACE_LEVEL 6

#if defined(SIMPLE_LOGGER_DISABLE_LOG)
#define SIMPLE_LOGGER_LOG_LEVEL SIMPLE_LOGGER_LOG_NONE_LEVEL
#elif defined(SIMPLE_LOGGER_ENABLE_LOG_TRACE)
#define SIMPLE_LOGGER_LOG_LEVEL SIMPLE_LOGGER_LOG_TRACE_LEVEL
#elif defined(SIMPLE_LOGGER_ENABLE_LOG_DEBUG)
#define SIMPLE_LOGGER_LOG_LEVEL SIMPLE_LOGGER_LOG_DEBUG_LEVEL
#elif defined(SIMPLE_LOGGER_ENABLE_LOG_INFO)
#define SIMPLE_LOGGER_LOG_LEVEL SIMPLE_LOGGER_LOG_INFO_LEVEL
#elif defined(SIMPLE_LOGGER_ENABLE_LOG_WARN)
#define SIMPLE_LOGGER_LOG_LEVEL SIMPLE_LOGGER_LOG_WARN_LEVEL
#elif defined(SIMPLE_LOGGER_ENABLE_LOG_ERROR)
#define SIMPLE_LOGGER_LOG_LEVEL SIMPLE_LOGGER_LOG_ERROR_LEVEL
#elif defined(SIMPLE_LOGGER_ENABLE_LOG_FATAL)
#define SIMPLE_LOGGER_LOG_LEVEL SIMPLE_LOGGER_LOG_FATAL_LEVEL
#else
#define SIMPLE_LOGGER_LOG_LEVEL SIMPLE_LOGGER_LOG_INFO_LEVEL
#endif

SIMPLE_LOGGER_NAMESPACE_BEGIN

template <bool ThreadSafe>
class Logger;

namespace details {

#include "details/colorctl.ipp"

using namespace std::literals::string_view_literals;
static constexpr std::string_view kTracePrompt = "trace"sv;
static constexpr std::string_view kDebugPrompt = "debug"sv;
static constexpr std::string_view kInfoPrompt  = "info"sv;
static constexpr std::string_view kWarnPrompt  = "warn"sv;
static constexpr std::string_view kErrorPrompt = "error"sv;
static constexpr std::string_view kFatalPrompt = "fatal"sv;

template <bool ThreadSafe>
class LoggerLock {
 private:
  static void Lock() {}
  static void Unlock() {}

  friend class Logger<ThreadSafe>;
};

template <>
class LoggerLock<true> {
 private:
  static inline std::mutex lock;

 private:
  static void Lock() { lock.lock(); }
  static void Unlock() { lock.unlock(); }

  friend class Logger<true>;
};

}  // namespace details

template <bool ThreadSafe>
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
      auto functy = [this] {
        this->postfix_();
        this->os_ << std::endl;
      };

      if constexpr (ThreadSafe) {
        try {
          functy();
        } catch (...) {
          details::LoggerLock<ThreadSafe>::Unlock();
          throw;
        }
        details::LoggerLock<ThreadSafe>::Unlock();
      } else {
        functy();
      }
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
  auto Trace() {
#if SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_TRACE_LEVEL
    return this->StdoutLog(details::kBeginBlue, details::kTracePrompt);
#else
    return EmptyLogHelper();
#endif  // SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_TRACE_LEVEL
  }

  template <typename... Vals>
  void Trace(Vals&&... vals) {
    (this->Trace() << ... << std::forward<Vals>(vals));
  }

  template <typename... Args>
  void Tracef(fmt::format_string<Args...> fmt, Args&&... args) {
    this->Trace() << fmt::format(fmt, std::forward<Args>(args)...);
  }

  auto Debug() {
#if SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_DEBUG_LEVEL
    return this->StdoutLog(details::kBeginGreen, details::kDebugPrompt);
#else
    return EmptyLogHelper();
#endif  // SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_DEBUG_LEVEL
  }

  template <typename... Vals>
  void Debug(Vals&&... vals) {
    (this->Debug() << ... << std::forward<Vals>(vals));
  }

  template <typename... Args>
  void Debugf(fmt::format_string<Args...> fmt, Args&&... args) {
    this->Debug() << fmt::format(fmt, std::forward<Args>(args)...);
  }

  auto Info() {
#if SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_INFO_LEVEL
    return this->StdoutLog(details::kInfoPrompt);
#else
    return EmptyLogHelper();
#endif  // SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_INFO_LEVEL
  }

  template <typename... Vals>
  void Info(Vals&&... vals) {
    (this->Info() << ... << std::forward<Vals>(vals));
  }

  template <typename... Args>
  void Infof(fmt::format_string<Args...> fmt, Args&&... args) {
    this->Info() << fmt::format(fmt, std::forward<Args>(args)...);
  }

  auto Warn() {
#if SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_WARN_LEVEL
    return this->StderrLog(details::kBeginYellow, details::kWarnPrompt);
#else
    return EmptyLogHelper();
#endif  // SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_WARN_LEVEL
  }

  template <typename... Vals>
  void Warn(Vals&&... vals) {
    (this->Warn() << ... << std::forward<Vals>(vals));
  }

  template <typename... Args>
  void Warnf(fmt::format_string<Args...> fmt, Args&&... args) {
    this->Warn() << fmt::format(fmt, std::forward<Args>(args)...);
  }

  auto Error() {
#if SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_ERROR_LEVEL
    return this->StderrLog(details::kBeginRed, details::kErrorPrompt);
#else
    return EmptyLogHelper();
#endif  // SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_ERROR_LEVEL
  }

  template <typename... Vals>
  void Error(Vals&&... vals) {
    (this->Error() << ... << std::forward<Vals>(vals));
  }

  template <typename... Args>
  void Errorf(fmt::format_string<Args...> fmt, Args&&... args) {
    this->Error() << fmt::format(fmt, std::forward<Args>(args)...);
  }

  auto Fatal() {
#if SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_FATAL_LEVEL
    return this->StderrLog(details::kBeginRed, details::kFatalPrompt);
#else
    return EmptyLogHelper();
#endif  // SIMPLE_LOGGER_LOG_LEVEL >= SIMPLE_LOGGER_LOG_FATAL_LEVEL
  }

  template <typename... Vals>
  void Fatal(Vals&&... vals) {
    (this->Fatal() << ... << std::forward<Vals>(vals));
  }

  template <typename... Args>
  void Fatalf(fmt::format_string<Args...> fmt, Args&&... args) {
    this->Fatal() << fmt::format(fmt, std::forward<Args>(args)...);
  }

 private:
  void PrintTime(std::ostream& os) {
    os << fmt::format("{:%Y-%m-%d %H:%M:%S} ",
                      fmt::localtime(std::chrono::system_clock::to_time_t(
                          std::chrono::system_clock::now())));
  }

  LogHelper StdoutLog(details::ColorCtlType token, std::string_view level) {
    auto functy = [&] {
      auto end_token = details::GetOutputEndColorToken();
      details::SetOutputColor(token);
      Logger::PrintTime(std::cout);
      std::cout << '[' << level << "] ";
      return LogHelper(std::cout, [=] { details::SetOutputColor(end_token); });
    };
    return this->HandleThreadSafe(functy);
  }

  LogHelper StdoutLog(std::string_view level) {
    auto functy = [&] {
      Logger::PrintTime(std::cout);
      std::cout << '[' << level << "] ";
      return LogHelper(std::cout, [] {});
    };
    return this->HandleThreadSafe(functy);
  }

  LogHelper StderrLog(details::ColorCtlType token, std::string_view level) {
    auto functy = [&] {
      auto end_token = details::GetErrorEndColorToken();
      details::SetErrorColor(token);
      Logger::PrintTime(std::cerr);
      std::cerr << '[' << level << "] ";
      return LogHelper(std::cerr, [=] { details::SetErrorColor(end_token); });
    };
    return this->HandleThreadSafe(functy);
  }

  LogHelper StderrLog(std::string_view level) {
    auto functy = [&] {
      Logger::PrintTime(std::cerr);
      std::cerr << '[' << level << "] ";
      return LogHelper(std::cerr, [] {});
    };
    return this->HandleThreadSafe(functy);
  }

  template <typename Functy>
  LogHelper HandleThreadSafe(Functy&& functy) {
    if constexpr (ThreadSafe) {
      details::LoggerLock<ThreadSafe>::Lock();
      try {
        return functy();
      } catch (...) {
        details::LoggerLock<ThreadSafe>::Unlock();
        throw;
      }
    } else {
      return functy();
    }
  }
};

inline Logger<true>  logger;    // Thread-safe
inline Logger<false> uslogger;  // Thread-unsafe

SIMPLE_LOGGER_NAMESPACE_END

#endif  // SIMPLE_LOGGER_HPP_
