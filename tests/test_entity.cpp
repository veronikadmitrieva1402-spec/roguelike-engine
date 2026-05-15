#include <catch2/catch_test_macros.hpp>
#include "../include/Entity.h"

TEST_CASE("Entity creation", "[entity]") {
    Entity e("Hero", 100, 20, 10);
    
    SECTION("Constructor sets name") {
        REQUIRE(e.getName() == "Hero");
    }
    
    SECTION("Constructor sets max HP") {
        REQUIRE(e.getMaxHP() == 100);
    }
    
    SECTION("Constructor sets current HP to max") {
        REQUIRE(e.getCurrentHP() == 100);
    }
    
    SECTION("Constructor sets attack") {
        REQUIRE(e.getAttack() == 20);
    }
    
    SECTION("Constructor sets protection") {
        REQUIRE(e.getProtection() == 10);
    }
    
    SECTION("Entity is alive after creation") {
        REQUIRE(e.isAlive() == true);
    }
    
    SECTION("Default position is (0,0)") {
        Position pos = e.getPosition();
        REQUIRE(pos.x == 0);
        REQUIRE(pos.y == 0);
    }
}

TEST_CASE("Entity damage", "[entity]") {
    Entity e("Hero", 100, 20, 10);
    
    SECTION("Take normal damage") {
        e.takeDamage(50);
        REQUIRE(e.getCurrentHP() == 60);
    }
    
    SECTION("Take damage reduced by protection") {
        e.takeDamage(10);
        REQUIRE(e.getCurrentHP() == 100);
    }
    
    SECTION("Take damage with protection") {
        e.takeDamage(30);
        REQUIRE(e.getCurrentHP() == 80);
    }
    
    SECTION("Take lethal damage") {
        e.takeDamage(200);
        REQUIRE(e.getCurrentHP() == 0);
        REQUIRE(e.isAlive() == false);
    }
    
    SECTION("HP does not go below 0") {
        e.takeDamage(500);
        REQUIRE(e.getCurrentHP() == 0);
    }
}

TEST_CASE("Entity position", "[entity]") {
    Entity e("Hero", 100, 20, 10);
    
    SECTION("Set position") {
        e.setPosition(5, 10);
        Position pos = e.getPosition();
        REQUIRE(pos.x == 5);
        REQUIRE(pos.y == 10);
    }
    
    SECTION("Set negative position") {
        e.setPosition(-1, -5);
        Position pos = e.getPosition();
        REQUIRE(pos.x == -1);
        REQUIRE(pos.y == -5);
    }
    
    SECTION("Set zero position") {
        e.setPosition(0, 0);
        Position pos = e.getPosition();
        REQUIRE(pos.x == 0);
        REQUIRE(pos.y == 0);
    }
}

TEST_CASE("Entity setters", "[entity]") {
    Entity e("Hero", 100, 20, 10);
    
    SECTION("Set HP") {
        e.setCurrentHP(50);
        REQUIRE(e.getCurrentHP() == 50);
    }
    
    SECTION("Set attack") {
        e.setAttack(30);
        REQUIRE(e.getAttack() == 30);
    }
    
    SECTION("Set protection") {
        e.setProtection(15);
        REQUIRE(e.getProtection() == 15);
    }
}
