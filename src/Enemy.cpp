#include "../include/Enemy.h"
#include <iostream>

Enemy::Enemy(const std::string& id, const std::string& name, int maxHP, int attack, 
            int protection, const std::string& description)
    : Entity(name, maxHP, attack, protection), id(id), description(description) {}

std::string Enemy::getId() const { return id; }

void Enemy::displayInfo() const {
    Entity::displayInfo();
    std::cout << "Описание: " << description << std::endl;
}