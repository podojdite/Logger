add_executable(LoggerApp LoggerApp.cpp)

# Линк к библиотеке
target_link_libraries(LoggerApp PRIVATE LoggerLib)

# Путь к заголовкам
target_include_directories(LoggerApp PRIVATE ${CMAKE_SOURCE_DIR}/LoggerLib)

# Добавление флага импорта (для DLL)
target_compile_definitions(LoggerApp PRIVATE LOGGERLIB_IMPORTS)
