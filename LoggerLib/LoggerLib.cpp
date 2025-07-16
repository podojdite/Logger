#include "LoggerLib.h"
#include <fstream>
#include <ctime>
#include <locale>
#include <codecvt>

namespace LogLib
{

    Logger::Logger(const std::string &filename, Level defaultLevel)
        : logFileName(filename), currentLevel(defaultLevel) {}

    Logger::~Logger() {}

    // Метод для записи лога
    void Logger::log(const std::string &message, Level level)
    {
        if (level < currentLevel)
            return;

        std::ofstream out(logFileName, std::ios::app);
        if (out.is_open())
        {
            out << "[" << getTimestamp() << "]"
                << " [" << levelToString(level) << "] "
                << message << std::endl;
        }
    }

    // Метод для изменения уровня важности
    void Logger::setLevel(Level newLevel)
    {
        currentLevel = newLevel;
    }

    Level Logger::getLevel() const
    {
        return currentLevel;
    }

    // Функция, возвращающая время в формате YYYY-MM-DD HH:MM:SS
    std::string Logger::getTimestamp() const
    {
        time_t now = time(0);
        char buf[20];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
        return std::string(buf);
    }

    // Вспомогательная функция
    std::string Logger::levelToString(Level level) const
    {
        switch (level)
        {
        case Level::Info:
            return "INFO";
        case Level::Warning:
            return "WARNING";
        case Level::Error:
            return "ERROR";
        default:
            return "UNKNOWN";
        }
    }

}