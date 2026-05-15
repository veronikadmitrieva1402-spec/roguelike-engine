#include "../include/Player.h"
#include "../include/GameWorld.h"
#include "../include/Logger.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include <string>

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
    bool levelComplete = false;
    
    while (running && player.isAlive()) {
        system("cls");
        
        player.displayInfo();
        std::cout << "Уровень: " << currentLevel + 1 << std::endl << std::endl;
        world.display();
        
        std::cout << "\nWASD - движение | G - подобрать | I - инвентарь | E - переход | Q - выход" << std::endl;
        
        Position pos = player.getPosition();
        if (world.isExit(pos.x, pos.y)) {
            std::cout << ">>> Нажмите E для перехода на следующий уровень <<<" << std::endl;
        }
        
        char key = _getch();
        
        switch (key) {
            case 'w': case 'W': player.move(0, -1, world); break;
            case 's': case 'S': player.move(0, 1, world); break;
            case 'a': case 'A': player.move(-1, 0, world); break;
            case 'd': case 'D': player.move(1, 0, world); break;
            case 'g': case 'G':
                player.pickUpItem(world);
                std::cout << "Нажмите любую клавишу...";
                _getch();
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
                _getch();
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
                        _getch();
                        running = false;
                    }
                } else {
                    std::cout << "Здесь нет выхода. Нажмите любую клавишу...";
                    _getch();
                }
                break;
            case 'q': case 'Q':
                running = false;
                break;
        }
    }
    
    if (!player.isAlive()) {
        system("cls");
        std::cout << "ИГРА ОКОНЧЕНА! Вы погибли." << std::endl;
        std::cout << "Нажмите любую клавишу...";
        _getch();
    }
    
    Logger::getInstance().log(" Roguelike Engine Stopped ");
    return 0;
}