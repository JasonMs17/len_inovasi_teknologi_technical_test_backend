#include "Logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>

namespace leniot {
namespace logger {

std::string getLevelString(LogLevel level) {
    switch(level) {
        case LogLevel::DEBUG:   return "DEBUG";
        case LogLevel::INFO:    return "INFO";
        case LogLevel::WARNING: return "WARN";
        case LogLevel::ERROR:   return "ERROR";
        default:                return "UNKNOWN";
    }
}

void log(LogLevel level, const std::string& message) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    
    struct tm* timeinfo = std::localtime(&now_c);
    
    char buffer[80];
    std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    
    std::cout << "[" << buffer << "] [" << getLevelString(level) << "] " << message << "\n";
}

void info(const std::string& message) {
    log(LogLevel::INFO, message);
}

void error(const std::string& message) {
    log(LogLevel::ERROR, message);
}

} // namespace logger
} // namespace leniot
