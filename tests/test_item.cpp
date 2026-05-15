#include <catch2/catch_test_macros.hpp>
#include "../include/Item.h"
#include "../include/Player.h"

TEST_CASE("Item creation", "[item]") {
    Item potion("potion_01", "Зелье", "potion", "heal", 25, "Лечит 25 HP");
    
    SECTION("Constructor sets id") {
        REQUIRE(potion.getId() == "potion_01");
    }
    
    SECTION("Constructor sets name") {
        REQUIRE(potion.getName() == "Зелье");
    }
    
    SECTION("Constructor sets type") {
        REQUIRE(potion.getType() == "potion");
    }
    
    SECTION("Constructor sets effect type") {
        REQUIRE(potion.getEffectType() == "heal");
    }
    
    SECTION("Constructor sets effect value") {
        REQUIRE(potion.getEffectValue() == 25);
    }
    
    SECTION("Constructor sets description") {
        REQUIRE(potion.getDescription() == "Лечит 25 HP");
    }
}

TEST_CASE("Item use - healing", "[item]") {
    Player& player = Player::getInstance();
    player.setCurrentHP(50);
    
    Item potion("potion_01", "Зелье", "potion", "heal", 25, "Лечит 25 HP");
    
    SECTION("Healing increases HP") {
        potion.use(player);
        REQUIRE(player.getCurrentHP() == 75);
    }
    
    SECTION("Healing does not exceed max HP") {
        potion.use(player);
        potion.use(player);
        potion.use(player);
        REQUIRE(player.getCurrentHP() <= player.getMaxHP());
    }
}

TEST_CASE("Item use - attack bonus", "[item]") {
    Player& player = Player::getInstance();
    int originalAttack = player.getAttack();
    
    Item sword("sword_01", "Меч", "weapon", "attack_bonus", 10, "Атака +10");
    
    SECTION("Attack increases") {
        sword.use(player);
        REQUIRE(player.getAttack() == originalAttack + 10);
    }
    
    SECTION("Multiple attack bonuses stack") {
        sword.use(player);
        sword.use(player);
        REQUIRE(player.getAttack() == originalAttack + 20);
    }
}

TEST_CASE("Item use - protection bonus", "[item]") {
    Player& player = Player::getInstance();
    int originalProtection = player.getProtection();
    
    Item armor("armor_01", "Броня", "armor", "protection_bonus", 5, "Защита +5");
    
    SECTION("Protection increases") {
        armor.use(player);
        REQUIRE(player.getProtection() == originalProtection + 5);
    }
}