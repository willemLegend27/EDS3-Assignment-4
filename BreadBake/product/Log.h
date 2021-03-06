#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <cstddef>

class Log
{

public:
    Log() = default;
    Log(Log const &) = delete;
    void operator=(Log const &) = delete;

    virtual void Debug(const char *fmt, ...);
    virtual void Trace(const char *fmt, ...);

private:
    void Write(bool enabled, const char *fmt, va_list ap);
};

#endif
