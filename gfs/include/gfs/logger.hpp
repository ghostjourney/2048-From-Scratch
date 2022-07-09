#pragma once

#include <iostream>
#include <string>

namespace gfs {

class Logger {
    public:
    enum class Level {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    virtual void Log(Level level, std::string message)=0;

    virtual void LogFatal(std::string message)=0;

    virtual void LogError(std::string message)=0;

    std::string LevelToString(const Level level) {
        switch(level) {
            case Level::TRACE:
                return "TRACE";
            case Level::DEBUG:
                return "DEBUG";
            case Level::INFO:
                return "INFO";
            case Level::WARN:
                return "WARN";
            case Level::ERROR:
                return "ERROR";
            case Level::FATAL:
                return "FATAL";
        }
    }
};
}
