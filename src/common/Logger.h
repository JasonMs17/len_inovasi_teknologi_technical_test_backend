#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace leniot {
namespace logger {

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

void log(LogLevel level, const std::string& message);
void info(const std::string& message);
void error(const std::string& message);

} // namespace logger
} // namespace leniot

#endif // LOGGER_H
