#include "../include/Player.h"
#include "../include/GameWorld.h"
#include "../include/Logger.h"
#include "../include/MapLoader.h"
#include "../include/JsonParser.h"
#include <iostream>
#include <conio.h>

int main() {
    Logger::getInstance().log(" Roguelike Engine Started ");
    
    GameWorld& world = GameWorld::getInstance();
    
    if (!world.loadMap("mods/map.csv")) {
        Logger::getInstance().log("Не удалось загрузить карту. Выход.");
        return 1;
    }
    
    Player& player = Player::getInstance();
    player.loadFromJson("mods/player.json");
    
    world.loadEnemies("mods/enemies.json");
    world.loadItems("mods/items.json");
    world.spawnEntitiesFromMap();

    bool running = true;
    while (running && player.isAlive()) {
        system("cls");
        
        player.displayInfo();
        std::cout << std::endl;
        world.display();
        
        std::cout << "\nWASD - движение | G - подобрать | I - инвентарь | Q - выход" << std::endl;
        
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
            case 'q': case 'Q':
                running = false;
                break;
        }
    }
    
    if (!player.isAlive()) {
        std::cout << "ИГРА ОКОНЧЕНА! Вы погибли." << std::endl;
    }
    
    Logger::getInstance().log(" Roguelike Engine Stopped ");
    return 0;
}