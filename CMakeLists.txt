cmake_minimum_required(VERSION 3.15)
project(Logger)

# Общая папка для всех собранных файлов (EXE/DLL/LIB и т.д.)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# Выбор статической или динамической сборки
option(BUILD_SHARED_LIBS "Build shared libraries (.dll/.so) instead of static (.lib/.a)" ON)

# Подпроекты
add_subdirectory(LoggerLib)
add_subdirectory(LoggerApp)
