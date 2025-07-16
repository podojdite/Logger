#pragma once

#include <string>

// Реализация статической/динамической бибилотеки
#if defined(LOGGERLIB_EXPORTS)
#define LOGGER_API __declspec(dllexport)
#elif defined(LOGGERLIB_IMPORTS)
#define LOGGER_API __declspec(dllimport)
#else
#define LOGGER_API
#endif

namespace LogLib
{

    enum class Level
    {
        Info,    // Уровень 0
        Warning, // Уровень 1
        Error,   // Уровень 2
        Unknown  // Уровень 3
    };

    class LOGGER_API Logger
    {
    public:
        Logger(const std::string &filename, Level defaultLevel);
        ~Logger();

        // Метод для записи лога
        void log(const std::string &message, Level level);

        // Метод для изменения уровня важности
        void setLevel(Level newLevel);
        Level getLevel() const;

    private:
        std::string logFileName;
        Level currentLevel;

        // Функция, возвращающая время в формате YYYY-MM-DD HH:MM:SS
        std::string getTimestamp() const;
        // Вспомогательная функция
        std::string levelToString(Level level) const;
    };

}
