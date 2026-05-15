#include <catch2/catch_test_macros.hpp>
#include "../include/Player.h"
#include "../include/Item.h"

TEST_CASE("Player singleton", "[player]") {
    Player& p1 = Player::getInstance();
    Player& p2 = Player::getInstance();
    
    SECTION("Same instance") {
        REQUIRE(&p1 == &p2);
    }
}

TEST_CASE("Player default stats", "[player]") {
    Player& player = Player::getInstance();
    
    SECTION("Default name") {
        REQUIRE(player.getName() == "Hero");
    }
    
    SECTION("Default HP") {
        REQUIRE(player.getMaxHP() == 100);
        REQUIRE(player.getCurrentHP() == 100);
    }
    
    SECTION("Default attack") {
        REQUIRE(player.getAttack() == 15);
    }
    
    SECTION("Default protection") {
        REQUIRE(player.getProtection() == 5);
    }
    
    SECTION("Player is alive") {
        REQUIRE(player.isAlive() == true);
    }
    
    SECTION("Default position is (0,0)") {
        REQUIRE(player.getPosition().x >= 0);
        REQUIRE(player.getPosition().y >= 0);
    }
}

TEST_CASE("Player damage and death", "[player]") {
    Player& player = Player::getInstance();
    
    SECTION("Take damage reduces HP") {
        player.setCurrentHP(100);
        player.takeDamage(30);
        REQUIRE(player.getCurrentHP() == 75);
    }
    
    SECTION("Take damage with protection") {
        player.setCurrentHP(100);
        player.setProtection(10);
        player.takeDamage(20);
        REQUIRE(player.getCurrentHP() == 90);
    }
    
    SECTION("Lethal damage kills player") {
        player.setCurrentHP(10);
        player.takeDamage(100);
        REQUIRE(player.getCurrentHP() == 0);
        REQUIRE(player.isAlive() == false);
    }
    
    SECTION("HP never below 0") {
        player.setCurrentHP(5);
        player.takeDamage(999);
        REQUIRE(player.getCurrentHP() == 0);
    }
    
    SECTION("Zero damage does nothing") {
        player.setCurrentHP(50);
        player.takeDamage(0);
        REQUIRE(player.getCurrentHP() == 50);
    }
    
    SECTION("Protection blocks all damage") {
        player.setCurrentHP(50);
        player.setProtection(100);
        player.takeDamage(10);
        REQUIRE(player.getCurrentHP() == 50);
    }
}

TEST_CASE("Player setters", "[player]") {
    Player& player = Player::getInstance();
    
    SECTION("Set HP") {
        player.setCurrentHP(75);
        REQUIRE(player.getCurrentHP() == 75);
    }
    
    SECTION("Set attack") {
        player.setAttack(25);
        REQUIRE(player.getAttack() == 25);
    }
    
    SECTION("Set protection") {
        player.setProtection(15);
        REQUIRE(player.getProtection() == 15);
    }
}

TEST_CASE("Player inventory", "[player]") {
    Player& player = Player::getInstance();
    
    
    SECTION("Add item to inventory") {
        Item* potion = new Item("test_01", "Тестовое зелье", "potion", "heal", 10, "");
        player.addItem(potion);
        REQUIRE_NOTHROW(player.showInventory());
    }
    
    SECTION("Use item from inventory") {
        player.setCurrentHP(50);
        Item* potion = new Item("test_02", "Зелье HP", "potion", "heal", 20, "");
        REQUIRE_NOTHROW(player.showInventory());
    }
    
    SECTION("Use item with wrong index") {
        REQUIRE_NOTHROW(player.useItem(999));
        REQUIRE_NOTHROW(player.useItem(-1));
    }
    
    SECTION("Show empty inventory") {
        REQUIRE_NOTHROW(player.showInventory());
    }
}

TEST_CASE("Player load from JSON", "[player]") {
    Player& player = Player::getInstance();
    
    SECTION("Load valid JSON") {
        REQUIRE_NOTHROW(player.loadFromJson("D:/PKS_Corse/mods/player.json"));
    }
    
    SECTION("Load sets correct name") {
        player.loadFromJson("D:/PKS_Corse/mods/player.json");
        REQUIRE(player.getName() == "Hero");
    }
    
    SECTION("Load sets HP") {
        player.loadFromJson("D:/PKS_Corse/mods/player.json");
        REQUIRE(player.getMaxHP() == 100);
    }
    
    SECTION("Load sets position from JSON") {
        player.loadFromJson("D:/PKS_Corse/mods/player.json");
        Position pos = player.getPosition();
        REQUIRE(pos.x == 1);
        REQUIRE(pos.y == 1);
    }
    
    SECTION("Load invalid file does not crash") {
        REQUIRE_NOTHROW(player.loadFromJson("nonexistent.json"));
    }
}

TEST_CASE("Player position", "[player]") {
    Player& player = Player::getInstance();
    
    SECTION("Set and get position") {
        player.setPosition(10, 5);
        REQUIRE(player.getPosition().x == 10);
        REQUIRE(player.getPosition().y == 5);
    }
    
    SECTION("Default position") {
        player.loadFromJson("D:/PKS_Corse/mods/player.json");
        Position pos = player.getPosition();
        REQUIRE(pos.x >= 0);
        REQUIRE(pos.y >= 0);
    }
}