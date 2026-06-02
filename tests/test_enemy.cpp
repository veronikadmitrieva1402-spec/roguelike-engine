#include <catch2/catch_test_macros.hpp>
#include "Enemy.h"

TEST_CASE("Enemy creation", "[enemy]") {
    Enemy goblin("gob_01", "Goblin", 50, 10, 3, "Злобный гоблин");
    
    SECTION("Constructor sets id") {
        REQUIRE(goblin.getId() == "gob_01");
    }
    
    SECTION("Constructor sets name") {
        REQUIRE(goblin.getName() == "Goblin");
    }
    
    SECTION("Constructor sets HP") {
        REQUIRE(goblin.getMaxHP() == 50);
        REQUIRE(goblin.getCurrentHP() == 50);
    }
    
    SECTION("Constructor sets attack") {
        REQUIRE(goblin.getAttack() == 10);
    }
    
    SECTION("Constructor sets protection") {
        REQUIRE(goblin.getProtection() == 3);
    }
    
    SECTION("Constructor sets description") {
        REQUIRE(goblin.getDescription() == "Злобный гоблин");
    }
    
    SECTION("Enemy is alive") {
        REQUIRE(goblin.isAlive() == true);
    }
}

TEST_CASE("Enemy damage", "[enemy]") {
    Enemy goblin("gob_01", "Goblin", 50, 10, 3, "");
    
    SECTION("Take damage") {
        goblin.takeDamage(20);
        REQUIRE(goblin.getCurrentHP() == 33);
    }
    
    SECTION("Take lethal damage") {
        goblin.takeDamage(60);
        REQUIRE(goblin.getCurrentHP() == 0);
        REQUIRE(goblin.isAlive() == false);
    }
    
    SECTION("Protection reduces damage") {
        goblin.takeDamage(3);
        REQUIRE(goblin.getCurrentHP() == 50);
    }
}

TEST_CASE("Enemy position", "[enemy]") {
    Enemy goblin("gob_01", "Goblin", 50, 10, 3, "");
    
    SECTION("Set and get position") {
        goblin.setPosition(7, 3);
        REQUIRE(goblin.getPosition().x == 7);
        REQUIRE(goblin.getPosition().y == 3);
    }
}