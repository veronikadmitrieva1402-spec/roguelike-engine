# Roguelike-движок с поддержкой модов

Консольный движок для игр жанра roguelike с возможностью изменения игрового контента через внешние JSON и CSV файлы без перекомпиляции кода.

## Сборка

```bash
cmake -S . -B build
cmake --build build
```
## Запуск

```bash
cd build
.\Debug\RoguelikeEngine.exe

```

## Использованные библиотеки

nlohmann/json - парсинг JSON-файлов 