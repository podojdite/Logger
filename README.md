# Logger

Консольное многопоточное приложение использования библиотеки логирования на C++

## Структура проекта
- **LoggerLib** - Библиотека для записи логов
- **LoggerApp** - Консольное приложение для тестирования

## Сборка на Windows
```
run.bat <static|dynamic> <log file> <info|warning|error>
```

## Запуск на Windows
```
build/bin/Release/LoggerApp.exe <log file> <info|warning|error>
```

## Формат ввода
```
<сообщение>/<уровень>
```
Пример:
```
Ошибка входа/error
Информация/info
exit
```