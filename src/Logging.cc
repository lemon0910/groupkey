#include <Logging.h>

#include <Timestamp.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <sstream>

/*
class MyLoggerImpl
{
 public:
  typedef MyLogger::LogLevel LogLevel;
  MyLoggerImpl(LogLevel level, int old_errno, const char* file, int line);
  void finish();

  Timestamp time_;
  LogStream stream_;
  LogLevel level_;
  int line_;
  const char* fullname_;
  const char* basename_;
};
*/

char t_errnobuf[512];
char t_time[32];
time_t t_lastSecond;

const char* strerror_tl(int savedErrno)
{
  return strerror_r(savedErrno, t_errnobuf, sizeof t_errnobuf);
}

MyLogger::LogLevel initLogLevel()
{
  if (::getenv("MUDUO_LOG_TRACE"))
    return MyLogger::TRACE;
  else if (::getenv("MUDUO_LOG_DEBUG"))
    return MyLogger::DEBUG;
  else
    return MyLogger::INFO;
}

MyLogger::LogLevel g_logLevel = initLogLevel();

const char* LogLevelName[MyLogger::NUM_LOG_LEVELS] =
{
  "TRACE ",
  "DEBUG ",
  "INFO  ",
  "WARN  ",
  "ERROR ",
  "FATAL ",
};

// helper class for known string length at compile time
class T
{
 public:
  T(const char* str, unsigned len)
    :str_(str),
     len_(len)
  {
    assert(strlen(str) == len_);
  }

  const char* str_;
  const unsigned len_;
};

inline LogStream& operator<<(LogStream& s, T v)
{
  s.append(v.str_, v.len_);
  return s;
}

inline LogStream& operator<<(LogStream& s, const MyLogger::SourceFile& v)
{
  s.append(v.data_, v.size_);
  return s;
}

void defaultOutput(const char* msg, int len)
{
  size_t n = fwrite(msg, 1, len, stdout);
  //FIXME check n
  (void)n;
}

void defaultFlush()
{
  fflush(stdout);
}

MyLogger::OutputFunc g_output = defaultOutput;
MyLogger::FlushFunc g_flush = defaultFlush;

MyLogger::Impl::Impl(LogLevel level, int savedErrno, const SourceFile& file, int line)
  : time_(Timestamp::now()),
    stream_(),
    level_(level),
    line_(line),
    basename_(file)
{
  formatTime();
  stream_ << T(LogLevelName[level], 6);
  if (savedErrno != 0)
  {
    stream_ << strerror_tl(savedErrno) << " (errno=" << savedErrno << ") ";
  }
}

void MyLogger::Impl::formatTime()
{
  int64_t microSecondsSinceEpoch = time_.microSecondsSinceEpoch();
  time_t seconds = static_cast<time_t>(microSecondsSinceEpoch / 1000000);
  int microseconds = static_cast<int>(microSecondsSinceEpoch % 1000000);
  if (seconds != t_lastSecond)
  {
    t_lastSecond = seconds;
    struct tm tm_time;
    ::localtime_r(&seconds, &tm_time); // FIXME TimeZone::fromUtcTime

    int len = snprintf(t_time, sizeof(t_time), "%4d%02d%02d %02d:%02d:%02d",
        tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
        tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
    assert(len == 17); (void)len;
  }
  Fmt us(".%06dZ ", microseconds);
  assert(us.length() == 9);
  stream_ << T(t_time, 17) << T(us.data(), 9);
}

void MyLogger::Impl::finish()
{
  stream_ << " - " << basename_ << ':' << line_ << '\n';
}

MyLogger::MyLogger(SourceFile file, int line)
  : impl_(INFO, 0, file, line)
{
}

MyLogger::MyLogger(SourceFile file, int line, LogLevel level, const char* func)
  : impl_(level, 0, file, line)
{
  impl_.stream_ << func << ' ';
}

MyLogger::MyLogger(SourceFile file, int line, LogLevel level)
  : impl_(level, 0, file, line)
{
}

MyLogger::MyLogger(SourceFile file, int line, bool toAbort)
  : impl_(toAbort?FATAL:ERROR, errno, file, line)
{
}

MyLogger::~MyLogger()
{
  impl_.finish();
  const LogStream::Buffer& buf(stream().buffer());
  g_output(buf.data(), buf.length());
  if (impl_.level_ == FATAL)
  {
    g_flush();
    abort();
  }
}

void MyLogger::setLogLevel(MyLogger::LogLevel level)
{
  g_logLevel = level;
}

void MyLogger::setOutput(OutputFunc out)
{
  g_output = out;
}

void MyLogger::setFlush(FlushFunc flush)
{
  g_flush = flush;
}
