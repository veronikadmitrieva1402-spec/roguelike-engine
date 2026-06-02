#pragma once
#include "Entity.h"
#include <vector>
#include <string>

class Item;

class Player : public Entity {
private:
    std::vector<Item*> inventory;
    Player();
    
public:
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    static Player& getInstance();
    void loadFromJson(const std::string& filePath);
    void addItem(Item* item);
    void useItem(int index);
    void showInventory() const;
    bool move(int dx, int dy, class GameWorld& world);
    void displayInfo() const override;
    void pickUpItem(class GameWorld& world);
};