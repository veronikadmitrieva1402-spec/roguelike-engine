#pragma once
#include <string>

class Player;

class Item {
protected:
    std::string id;
    std::string name;
    std::string type;
    int effectValue;
    std::string effectType;
    std::string description;

public:
    Item(const std::string& id, const std::string& name, const std::string& type,
        const std::string& effectType, int effectValue, const std::string& description);
    virtual ~Item() = default;

    std::string getName() const;
    std::string getId() const;
    std::string getType() const;
    std::string getEffectType() const;
    int getEffectValue() const;
    std::string getDescription() const;
    virtual void use(Player& player);
};