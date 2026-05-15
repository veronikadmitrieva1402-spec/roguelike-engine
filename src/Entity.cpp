#include "../include/Entity.h"
#include "../include/Logger.h"
#include <iostream>

Entity::Entity(const std::string &name, int maxHP, int attack, int protection)
    : name(name), maxHP(maxHP), currentHP(maxHP), attack(attack), protection(protection), pos({0, 0}) {}

std::string Entity::getName() const { return name; }
int Entity::getCurrentHP() const { return currentHP; }
int Entity::getMaxHP() const { return maxHP; }
int Entity::getAttack() const { return attack; }
int Entity::getProtection() const { return protection; }
void Entity::setCurrentHP(int hp) { currentHP = hp; }
void Entity::setAttack(int atk) { attack = atk; }
void Entity::setProtection(int prot) { protection = prot; }
Position Entity::getPosition() const { return pos; }


void Entity::setPosition(int x, int y)
{
    pos.x = x;
    pos.y = y;
}

void Entity::takeDamage(int damage)
{
    int actualDamage = damage - protection;
    if (actualDamage < 0)
        actualDamage = 0;
    currentHP -= actualDamage;
    if (currentHP < 0)
        currentHP = 0;

    Logger::getInstance().log(name + " получил " + std::to_string(actualDamage) + " урона. HP: " + std::to_string(currentHP));
}

bool Entity::isAlive() const { return currentHP > 0; }

void Entity::displayInfo() const
{
    std::cout << name << " | HP: " << currentHP << "/" << maxHP
            << " | ATK: " << attack << " | DEF: " << protection << std::endl;
}