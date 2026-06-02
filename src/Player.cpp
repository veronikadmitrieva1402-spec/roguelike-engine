#include "Player.h"
#include "Item.h"
#include "GameWorld.h"
#include "Logger.h"
#include "Enemy.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Player::Player() : Entity("Hero", 100, 15, 5) {}

Player& Player::getInstance() {
    static Player instance;
    return instance;
}

void Player::loadFromJson(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        Logger::getInstance().log("Ошибка: не удалось открыть " + filePath);
        return;
    }
    
    json data = json::parse(file);
    name = data["name"];
    maxHP = data["maxHP"];
    currentHP = data["currentHP"];
    attack = data["attack"];
    protection = data["protection"];
    pos.x = data["startPosition"]["x"];
    pos.y = data["startPosition"]["y"];
    
    Logger::getInstance().log("Игрок загружен: " + name);
}

void Player::addItem(Item* item) {
    inventory.push_back(item);
    Logger::getInstance().log("Подобран предмет: " + item->getName());
}

void Player::useItem(int index) {
    if (index >= 0 && index < static_cast<int>(inventory.size())) {
        inventory[index]->use(*this);
        delete inventory[index];
        inventory.erase(inventory.begin() + index);
    }
}

void Player::showInventory() const {
    std::cout << " ИНВЕНТАРЬ " << std::endl;
    if (inventory.empty()) {
        std::cout << "Пусто" << std::endl;
        return;
    }
    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << i << ". " << inventory[i]->getName() << std::endl;
    }
}

bool Player::move(int dx, int dy, GameWorld& world) {
    int newX = pos.x + dx;
    int newY = pos.y + dy;
    
    if (!world.isWalkable(newX, newY)) {
        Logger::getInstance().log("Путь заблокирован");
        return false;
    }
    
    Enemy* enemy = world.getEnemyAt(newX, newY);
    if (enemy && enemy->isAlive()) {
        int damage = attack;
        enemy->takeDamage(damage);
        Logger::getInstance().log(name + " атакует " + enemy->getName() + " на " + std::to_string(damage) + " урона");
        
        if (enemy->isAlive()) {
            int enemyDamage = enemy->getAttack();
            takeDamage(enemyDamage);
            Logger::getInstance().log(enemy->getName() + " атакует в ответ на " + std::to_string(enemyDamage) + " урона");
        } else {
            Logger::getInstance().log(enemy->getName() + " повержен!");
            world.removeEnemy(newX, newY);
        }
        return true;
    }
    
    pos.x = newX;
    pos.y = newY;
    Logger::getInstance().log(name + " переместился на (" + std::to_string(newX) + ", " + std::to_string(newY) + ")");
    return true;
}

void Player::pickUpItem(GameWorld& world) {
    Item* item = world.getItemAt(pos.x, pos.y);
    if (item) {
        Item* newItem = new Item(item->getId(), item->getName(), item->getType(), item->getEffectType(), item->getEffectValue(), item->getDescription());
        inventory.push_back(newItem);
        Logger::getInstance().log("Подобран предмет: " + newItem->getName());
        std::cout << "Подобран предмет: " << newItem->getName() << std::endl;
        world.removeItem(pos.x, pos.y);
    } else {
        std::cout << "Здесь нет предметов." << std::endl;
    }
}

void Player::displayInfo() const {
    Entity::displayInfo();
    std::cout << "Позиция: (" << pos.x << ", " << pos.y << ")" << std::endl;
}