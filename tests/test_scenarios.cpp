#include <catch2/catch_test_macros.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Item.h"

TEST_CASE("Scenario 1: Player attacks enemy and wins", "[scenario]") {
    Player& player = Player::getInstance();
    player.setCurrentHP(player.getMaxHP());
    player.setAttack(30);
    
    Enemy goblin("gob_01", "Goblin", 20, 5, 0, "");
    
    SECTION("Player kills enemy") {
        goblin.takeDamage(player.getAttack());
        REQUIRE(goblin.isAlive() == false);
        REQUIRE(player.isAlive() == true);
    }
}

TEST_CASE("Scenario 2: Player takes damage from enemy", "[scenario]") {
    Player& player = Player::getInstance();
    player.setCurrentHP(50);
    player.setProtection(2);
    
    Enemy goblin("gob_01", "Goblin", 30, 10, 0, "");
    
    SECTION("Player survives one hit") {
        player.takeDamage(goblin.getAttack());
        REQUIRE(player.getCurrentHP() == 42);
        REQUIRE(player.isAlive() == true);
    }
}

TEST_CASE("Scenario 3: Player dies from enemy attack", "[scenario]") {
    Player& player = Player::getInstance();
    player.setCurrentHP(5);
    
    Enemy boss("boss_01", "Boss", 100, 50, 0, "");
    
    SECTION("Player dies") {
        player.takeDamage(boss.getAttack());
        REQUIRE(player.isAlive() == false);
    }
}

TEST_CASE("Scenario 4: Player uses healing potion", "[scenario]") {
    Player& player = Player::getInstance();
    player.setCurrentHP(40);
    int hpBefore = player.getCurrentHP();
    
    Item potion("pot_01", "Зелье", "potion", "heal", 30, "");
    
    SECTION("HP increases") {
        potion.use(player);
        REQUIRE(player.getCurrentHP() == hpBefore + 30);
    }
}

TEST_CASE("Scenario 5: Player picks up sword and attacks", "[scenario]") {
    Player& player = Player::getInstance();
    player.setAttack(20);
    
    Item sword("sword_01", "Меч", "weapon", "attack_bonus", 15, "");
    
    SECTION("Attack increases after using sword") {
        sword.use(player);
        REQUIRE(player.getAttack() == 35);
    }
}

TEST_CASE("Scenario 6: Multiple items usage", "[scenario]") {
    Player& player = Player::getInstance();
    player.setCurrentHP(10);
    player.setAttack(10);
    
    Item potion("pot_01", "Зелье", "potion", "heal", 20, "");
    Item sword("sword_01", "Меч", "weapon", "attack_bonus", 10, "");
    
    SECTION("HP and attack both change") {
        potion.use(player);
        sword.use(player);
        REQUIRE(player.getCurrentHP() == 30);
        REQUIRE(player.getAttack() == 20);
    }
}

TEST_CASE("Scenario 7: Player cannot heal above max HP", "[scenario]") {
    Player& player = Player::getInstance();
    player.setCurrentHP(95);
    int maxHP = player.getMaxHP();
    
    Item potion("pot_01", "Зелье", "potion", "heal", 50, "");
    
    SECTION("HP capped at max") {
        potion.use(player);
        REQUIRE(player.getCurrentHP() == maxHP);
    }
}