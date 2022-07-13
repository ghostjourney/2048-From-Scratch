#pragma once

#include <iostream>
#include <string>

namespace gfs {

/**
 * An abstract Logger for logging information
 */
class Logger {
    public:
    
    /**
     * Logging level for a given message
     */
    enum class Level {
        /// Trace information
        TRACE,
        /// Debug Information
        DEBUG,
        /// General Information
        INFO,
        /// Warnings
        WARN,
        /// Possibly Recoverable Errors
        ERROR,
        /// Nonrecoverable Errors
        FATAL
    };

    /**
     * Log the provided message with the provided level
     * \param level message logging level
     * \param message message to be logged
     */
    virtual void Log(Level level, std::string message)=0;

    /**
     * Log Fatal Message
     * \param message message to be logged
     */
    virtual void LogFatal(std::string message)=0;

    /**
     * Log Error Message
     * \param message message
     */
    virtual void LogError(std::string message)=0;

    /**
     * Converts the provided level to a string
     * \param level message level
     * \returns level as string
     */
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
