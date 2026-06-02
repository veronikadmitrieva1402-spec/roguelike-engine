#include "Player.h"
#include "GameWorld.h"
#include "Logger.h"
#include <iostream>
#include <vector>
#include <string>

#ifdef _WIN32
    #include <conio.h>
    #define CLEAR "cls"
    char getKey() { return _getch(); }
#else
    #include <termios.h>
    #include <unistd.h>
    #define CLEAR "clear"
    char getKey() {
        struct termios oldt, newt;
        char ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#endif

int main() {
    Logger::getInstance().log(" Roguelike Engine Started ");
    
    std::vector<std::string> levels = {
        "mods/map_level1.csv",
        "mods/map_level2.csv"
    };
    int currentLevel = 0;
    
    GameWorld& world = GameWorld::getInstance();
    Player& player = Player::getInstance();
    
    if (!world.loadMap(levels[currentLevel])) {
        Logger::getInstance().log("Не удалось загрузить карту. Выход.");
        return 1;
    }
    
    player.loadFromJson("mods/player.json");
    world.loadEnemies("mods/enemies.json");
    world.loadItems("mods/items.json");
    world.spawnEntitiesFromMap();
    
    bool running = true;
    
    while (running && player.isAlive()) {
        system(CLEAR);
        
        player.displayInfo();
        std::cout << "Уровень: " << currentLevel + 1 << std::endl << std::endl;
        world.display();
        
        std::cout << "\nWASD - движение | G - подобрать | I - инвентарь | E - переход | Q - выход" << std::endl;
        
        Position pos = player.getPosition();
        if (world.isExit(pos.x, pos.y)) {
            std::cout << ">>> Нажмите E для перехода на следующий уровень <<<" << std::endl;
        }
        
        char key = getKey();
        
        switch (key) {
            case 'w': case 'W': player.move(0, -1, world); break;
            case 's': case 'S': player.move(0, 1, world); break;
            case 'a': case 'A': player.move(-1, 0, world); break;
            case 'd': case 'D': player.move(1, 0, world); break;
            case 'g': case 'G':
                player.pickUpItem(world);
                std::cout << "Нажмите любую клавишу...";
                getKey();
                break;
            case 'i': case 'I':
                player.showInventory();
                std::cout << "Введите номер предмета для использования (-1 - отмена): ";
                int itemIndex;
                std::cin >> itemIndex;
                if (itemIndex >= 0) {
                    player.useItem(itemIndex);
                }
                std::cout << "Нажмите любую клавишу...";
                getKey();
                break;
            case 'e': case 'E':
                if (world.isExit(pos.x, pos.y)) {
                    currentLevel++;
                    if (currentLevel < static_cast<int>(levels.size())) {
                        std::cout << "Переход на уровень " << currentLevel + 1 << "..." << std::endl;
                        world.loadMap(levels[currentLevel]);
                        world.loadEnemies("mods/enemies.json");
                        world.loadItems("mods/items.json");
                        world.spawnEntitiesFromMap();
                        player.loadFromJson("mods/player.json");
                    } else {
                        std::cout << "Вы прошли все уровни!" << std::endl;
                        std::cout << "Нажмите любую клавишу...";
                        getKey();
                        running = false;
                    }
                } else {
                    std::cout << "Здесь нет выхода. Нажмите любую клавишу...";
                    getKey();
                }
                break;
            case 'q': case 'Q':
                running = false;
                break;
        }
    }
    
    if (!player.isAlive()) {
        system(CLEAR);
        std::cout << "ИГРА ОКОНЧЕНА! Вы погибли." << std::endl;
        std::cout << "Нажмите любую клавишу...";
        getKey();
    }
    
    Logger::getInstance().log(" Roguelike Engine Stopped ");
    return 0;
}