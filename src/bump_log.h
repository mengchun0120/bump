#ifndef INCLUDE_BUMP_LOG
#define INCLUDE_BUMP_LOG

#include <stdio.h>

namespace bump {

class Logger {
public:
    enum LogLevel {
        LEVEL_DEBUG,
        LEVEL_INFO,
        LEVEL_WARN,
        LEVEL_ERROR
    };

    static Logger& getSingleton();

    static bool initSingleton(const char* logFile, LogLevel minLevel);

    static const char* levelString(LogLevel level);

    ~Logger();

    void write(const char *format, ...);

    void logTime();

    LogLevel minLevel() const
    {
        return m_minLevel;
    }

    bool valid() const
    {
        return m_fp != nullptr;
    }

    void flush();

    void close();

private:
    Logger(const char* logFile, LogLevel minLevel);

    FILE *m_fp;
    LogLevel m_minLevel;
};

} // end of namespace bump

#ifdef ENABLE_LOG
#define LOG_WRITE(level, ...) \
    { \
        bump::Logger& logger = bump::Logger::getSingleton(); \
        if(logger.valid() && level >= logger.minLevel()) { \
            logger.logTime(); \
            logger.write(" %s:%d %s ", __FILE__, __LINE__, bump::Logger::levelString(level)); \
            logger.write(__VA_ARGS__); \
            logger.write("\n"); \
            logger.flush(); \
        } \
    }
#else
#define LOG_WRITE(level, ...)
#endif

#define LOG_DEBUG(...) \
    LOG_WRITE(bump::Logger::LEVEL_DEBUG, __VA_ARGS__)

#define LOG_INFO(...) \
    LOG_WRITE(bump::Logger::LEVEL_INFO, __VA_ARGS__)

#define LOG_WARN(...) \
    LOG_WRITE(bump::Logger::LEVEL_WARN, __VA_ARGS__)

#define LOG_ERROR(...) \
    LOG_WRITE(bump::Logger::LEVEL_ERROR, __VA_ARGS__)

#endif
