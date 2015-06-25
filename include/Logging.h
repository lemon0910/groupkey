#ifndef LOGGING_H
#define LOGGING_H

#include <LogStream.h>
#include <Timestamp.h>

class MyLogger
{
 public:
  enum LogLevel
  {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
    NUM_LOG_LEVELS,
  };

  // compile time calculation of basename of source file
  class SourceFile
  {
   public:
    template<int N>
    inline SourceFile(const char (&arr)[N])
      : data_(arr),
        size_(N-1)
    {
      const char* slash = strrchr(data_, '/'); // builtin function
      if (slash)
      {
        data_ = slash + 1;
        size_ -= static_cast<int>(data_ - arr);
      }
    }

    explicit SourceFile(const char* filename)
      : data_(filename)
    {
      const char* slash = strrchr(filename, '/');
      if (slash)
      {
        data_ = slash + 1;
      }
      size_ = static_cast<int>(strlen(data_));
    }

    const char* data_;
    int size_;
  };

  MyLogger(SourceFile file, int line);
  MyLogger(SourceFile file, int line, LogLevel level);
  MyLogger(SourceFile file, int line, LogLevel level, const char* func);
  MyLogger(SourceFile file, int line, bool toAbort);
  ~MyLogger();

  LogStream& stream() { return impl_.stream_; }

  static LogLevel logLevel();
  static void setLogLevel(LogLevel level);

  typedef void (*OutputFunc)(const char* msg, int len);
  typedef void (*FlushFunc)();
  static void setOutput(OutputFunc);
  static void setFlush(FlushFunc);

 private:

class Impl
{
 public:
  typedef MyLogger::LogLevel LogLevel;
  Impl(LogLevel level, int old_errno, const SourceFile& file, int line);
  void formatTime();
  void finish();

  Timestamp time_;
  LogStream stream_;
  LogLevel level_;
  int line_;
  SourceFile basename_;
};

  Impl impl_;

};

extern MyLogger::LogLevel g_logLevel;

inline MyLogger::LogLevel MyLogger::logLevel()
{
  return g_logLevel;
}

#define LOG_TRACE if (MyLogger::logLevel() <= MyLogger::TRACE) \
  MyLogger(__FILE__, __LINE__, MyLogger::TRACE, __func__).stream()
#define LOG_DEBUG if (MyLogger::logLevel() <= MyLogger::DEBUG) \
  MyLogger(__FILE__, __LINE__, MyLogger::DEBUG, __func__).stream()
#define LOG_INFO if (MyLogger::logLevel() <= MyLogger::INFO) \
  MyLogger(__FILE__, __LINE__).stream()
#define LOG_WARN MyLogger(__FILE__, __LINE__, MyLogger::WARN).stream()
#define LOG_ERROR MyLogger(__FILE__, __LINE__, MyLogger::ERROR).stream()
#define LOG_FATAL MyLogger(__FILE__, __LINE__, MyLogger::FATAL).stream()
#define LOG_SYSERR MyLogger(__FILE__, __LINE__, false).stream()
#define LOG_SYSFATAL MyLogger(__FILE__, __LINE__, true).stream()

const char* strerror_tl(int savedErrno);

// Taken from glog/logging.h
//
// Check that the input is non NULL.  This very useful in constructor
// initializer lists.

#define CHECK_NOTNULL(val) \
  CheckNotNull(__FILE__, __LINE__, "'" #val "' Must be non NULL", (val))

// A small helper for CHECK_NOTNULL().
template <typename T>
T* CheckNotNull(MyLogger::SourceFile file, int line, const char *names, T* ptr) {
  if (ptr == NULL) {
   MyLogger(file, line, MyLogger::FATAL).stream() << names;
  }
  return ptr;
}

#endif  // MUDUO_BASE_LOGGING_H
