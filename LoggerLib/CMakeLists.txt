# Создание библиотеки (зависит от BUILD_SHARED_LIBS)
add_library(LoggerLib LoggerLib.cpp)

# Путь к заголовочным файлам
target_include_directories(LoggerLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Макрос для управления экспортом символов (dllexport)
target_compile_definitions(LoggerLib PRIVATE LOGGERLIB_EXPORTS)