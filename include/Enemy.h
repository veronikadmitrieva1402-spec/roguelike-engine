#pragma once
#include "Entity.h"
#include <string>

class Enemy : public Entity {
private:
    std::string id;
    std::string description;

public:
    Enemy(const std::string& id, const std::string& name, int maxHP, int attack, 
        int protection, const std::string& description);
    
    std::string getId() const;
    std::string getDescription() const;
    void displayInfo() const override;
};