#pragma once

#include "logger.hpp"

namespace gfs {

class ConsoleLogger : public Logger {
    public:
    virtual ~ConsoleLogger() {}
    void Log(Logger::Level level, std::string message) override {
        std::cout << Logger::LevelToString(level) << ": " << message << std::endl;
    }

    void LogFatal(std::string message) override {
        Log(Logger::Level::FATAL, message);
    }

    void LogError(std::string message) override {
        Log(Logger::Level::ERROR, message);
    }
};
}
