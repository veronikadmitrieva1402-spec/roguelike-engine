# Roguelike-движок с поддержкой модов

Консольный движок для игр жанра roguelike. Загружает игровые данные из внешних JSON и CSV файлов. Позволяет изменять контент без перекомпиляции кода.


## Для игрока

### Управление

| Клавиша | Действие |

| **W A S D** | Перемещение персонажа |
| **G** | Подобрать предмет (на клетке с `+`) |
| **I** | Открыть инвентарь и использовать предмет |
| **E** | Переход на следующий уровень (на клетке с `>`) |
| **Q** | Выход из игры |

### Установка и запуск

```bash
cmake -S . -B build
cmake --build build

.\build\Debug\RoguelikeEngine.exe

```
### Запуск тестов 
docker build --target builder -t roguelike-tests .
docker run -it roguelike-tests bash -c "cd build && ctest -C Release --output-on-failure"
### Полный запуск
docker build -t roguelike-engine
docker run -it roguelike-engine