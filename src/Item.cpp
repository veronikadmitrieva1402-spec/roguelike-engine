#include "../include/Item.h"
#include "../include/Player.h"
#include "../include/Logger.h"
#include <iostream>  

Item::Item(const std::string& id, const std::string& name, const std::string& type,
        const std::string& effectType, int effectValue, const std::string& description)
    : id(id), name(name), type(type), effectType(effectType), 
    effectValue(effectValue), description(description) {}

std::string Item::getName() const { return name; }
std::string Item::getId() const { return id; }
std::string Item::getType() const { return type; }
std::string Item::getEffectType() const { return effectType; }
int Item::getEffectValue() const { return effectValue; }
std::string Item::getDescription() const { return description; }

void Item::use(Player& player) {
    if (effectType == "heal") {
        int newHP = player.getCurrentHP() + effectValue;
        if (newHP > player.getMaxHP()) newHP = player.getMaxHP();
        player.setCurrentHP(newHP);
        Logger::getInstance().log("Использовано " + name + ": +" + std::to_string(effectValue) + " HP");
        std::cout << "Здоровье увеличено на " << effectValue << "!" << std::endl;
    }
    else if (effectType == "attack_bonus") {
        player.setAttack(player.getAttack() + effectValue);
        Logger::getInstance().log("Использован " + name + ": атака +" + std::to_string(effectValue));
        std::cout << "Атака увеличена на " << effectValue << "!" << std::endl;
    }
    else if (effectType == "protection_bonus") {
        player.setProtection(player.getProtection() + effectValue);
        Logger::getInstance().log("Использован " + name + ": защита +" + std::to_string(effectValue));
        std::cout << "Защита увеличена на " << effectValue << "!" << std::endl;
    }
}