#pragma once
#include <string>

struct Position {
    int x;
    int y;
};

class Entity {
protected:
    std::string name;
    int maxHP;
    int currentHP;
    int attack;
    int protection;
    Position pos;

public:
    Entity(const std::string& name, int maxHP, int attack, int protection);
    virtual ~Entity() = default;

    std::string getName() const;
    int getCurrentHP() const;
    int getMaxHP() const;
    int getAttack() const;
    int getProtection() const;
    Position getPosition() const;
    void setPosition(int x, int y);
    
    void takeDamage(int damage);
    bool isAlive() const;
    
    virtual void displayInfo() const;
};