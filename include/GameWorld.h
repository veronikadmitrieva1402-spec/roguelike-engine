#pragma once
#include <vector>
#include <string>
#include "../include/Entity.h"

class Enemy;
class Item;

class GameWorld {
private:
    std::vector<std::string> map;
    std::vector<Enemy*> enemies;
    std::vector<Item*> items;
    std::vector<Position> itemPositions;
    
    std::vector<Enemy*> enemyTemplates; 
    std::vector<Item*> itemTemplates; 
    
    int width;
    int height;
    
    GameWorld();
    
public:
    GameWorld(const GameWorld&) = delete;
    GameWorld& operator=(const GameWorld&) = delete;

    static GameWorld& getInstance();
    ~GameWorld();
    
    bool loadMap(const std::string& filePath);
    bool isWalkable(int x, int y) const;
    bool isExit(int x, int y) const;
    void display() const;
    
    Enemy* getEnemyAt(int x, int y);
    void removeEnemy(int x, int y);
    
    Item* getItemAt(int x, int y);
    void removeItem(int x, int y);
    
    void loadEnemies(const std::string& filePath);
    void loadItems(const std::string& filePath);
    void spawnEntitiesFromMap();
    
    char getTile(int x, int y) const;
    int getWidth() const;
    int getHeight() const;
};