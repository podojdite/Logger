#include <iostream>
#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <windows.h>
#include <sstream>

#include "LoggerLib.h"

using namespace LogLib;

struct LogTask
{
    std::string message;
    Level level;
};

std::queue<LogTask> taskQueue;
std::mutex queueMutex;
std::condition_variable queueCV;
std::atomic<bool> running{true};

// Функция, выполняемая в отдельном потоке — записывает логи
void loggerThreadFunc(Logger &logger)
{
    while (running || !taskQueue.empty())
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        queueCV.wait(lock, []
                     { return !taskQueue.empty() || !running; });

        while (!taskQueue.empty())
        {
            LogTask task = taskQueue.front();
            taskQueue.pop();
            lock.unlock();

            logger.log(task.message, task.level);

            lock.lock();
        }
    }
}

// Парсинг уровня важности из строки
Level parseLevel(const std::string &str, Level defaultLevel)
{
    if (str == "info" || str == "INFO" || str == "Info")
        return Level::Info;
    if (str == "warning" || str == "WARNING" || str == "Warning")
        return Level::Warning;
    if (str == "error" || str == "ERROR" || str == "Error")
        return Level::Error;
    return Level::Unknown;
}

int main(int argc, char *argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    if (argc < 3)
    {
        std::cerr << "Usage example: LoggerApp.exe <logfile> <default_level: info|warning|error>\n";
        return 1;
    }

    std::string logFile = argv[1];
    Level defaultLevel = parseLevel(argv[2], Level::Unknown);

    Logger logger(logFile, defaultLevel);

    std::thread loggerThread(loggerThreadFunc, std::ref(logger));

    bool help = true;

    while (true)
    {
        if (help == true)
        {
            std::cout << "Введите сообщения (формат: <текст>/<уровень>)\n"
                      << "Для изменения уровня важности сообщения по умолчанию напишите 'setlevel'\n"
                      << "Для вывода этой справки напишите 'help'\n"
                      << "Для выхода напишите 'exit'\n";
            help = false;
        }

        std::string inputLine;
        std::getline(std::cin, inputLine);
        std::istringstream iss(inputLine);

        if (inputLine == "exit")
            break;
        if (inputLine == "help")
            help = true;
        else
        {
            if (inputLine == "setlevel")
            {
                std::cout << "Выберите:\n1.Info\n2.Warning\n3.Error\n4.Отмена\n";
                std::string choiceStr;
                std::getline(std::cin, choiceStr);
                int choice = std::stoi(choiceStr);
                switch (choice)
                {
                case 1:
                    logger.setLevel(Level::Info);
                    std::cout << "Установлен уровень: Info\n";
                    break;

                case 2:
                    logger.setLevel(Level::Warning);
                    std::cout << "Установлен уровень: Warning\n";
                    break;

                case 3:
                    logger.setLevel(Level::Error);
                    std::cout << "Установлен уровень: Error\n";
                    break;

                case 4:
                    std::cout << "Отмена изменения уровня\n";
                    break;

                default:
                    std::cout << "Ошибка: введите число от 1 до 3\n";
                }
            }
            else
            {
                // Разделение строки: текст и уровень
                std::string message, levelStr;
                size_t spacePos = inputLine.rfind('/');
                if (spacePos != std::string::npos)
                {
                    message = inputLine.substr(0, spacePos);
                    std::getline(iss, levelStr, '/');
                    iss >> levelStr;
                }
                else
                {
                    message = inputLine;
                }
                Level msgLevel = parseLevel(levelStr, defaultLevel);

                {
                    std::lock_guard<std::mutex> lock(queueMutex);
                    taskQueue.push({message, msgLevel});
                }
                queueCV.notify_one();
            }
        }
    }
    // Завершаем
    running = false;
    queueCV.notify_one();
    loggerThread.join();

    std::cout << "Выход из программы.\n";
    return 0;
}
