#include <catch2/catch_test_macros.hpp>
#include "GameWorld.h"

TEST_CASE("GameWorld singleton", "[gameworld]") {
    GameWorld& gw1 = GameWorld::getInstance();
    GameWorld& gw2 = GameWorld::getInstance();
    
    SECTION("Same instance") {
        REQUIRE(&gw1 == &gw2);
    }
}

TEST_CASE("GameWorld map loading", "[gameworld]") {
    GameWorld& world = GameWorld::getInstance();
    
    SECTION("Load valid map") {
        REQUIRE(world.loadMap("/app/mods/map_level1.csv") == true);
    }
    
    SECTION("Load invalid map returns false") {
        REQUIRE(world.loadMap("nonexistent.csv") == false);
    }
    
    SECTION("Map dimensions after load") {
        world.loadMap("/app/mods/map_level1.csv");
        REQUIRE(world.getWidth() > 0);
        REQUIRE(world.getHeight() > 0);
    }
}

TEST_CASE("GameWorld walkable", "[gameworld]") {
    GameWorld& world = GameWorld::getInstance();
    world.loadMap("/app/mods/map_level1.csv");
    
    SECTION("Wall is not walkable") {
        REQUIRE(world.isWalkable(0, 0) == false);
    }
    
    SECTION("Floor is walkable") {
        REQUIRE(world.isWalkable(1, 1) == true);
    }
    
    SECTION("Out of bounds is not walkable") {
        REQUIRE(world.isWalkable(-1, -1) == false);
        REQUIRE(world.isWalkable(1000, 1000) == false);
    }
}

TEST_CASE("GameWorld exit detection", "[gameworld]") {
    GameWorld& world = GameWorld::getInstance();
    world.loadMap("/app/mods/map_level1.csv");
    
    int exitX = -1, exitY = -1;
    for (int y = 0; y < world.getHeight(); ++y) {
        for (int x = 0; x < world.getWidth(); ++x) {
            if (world.isExit(x, y)) {
                exitX = x;
                exitY = y;
            }
        }
    }
    
    SECTION("Exit tile exists") {
        REQUIRE(exitX != -1);
        REQUIRE(exitY != -1);
    }
    
    SECTION("Exit tile is detected") {
        REQUIRE(world.isExit(exitX, exitY) == true);
    }
    
    SECTION("Non-exit tile is not detected") {
        REQUIRE(world.isExit(1, 1) == false);
    }
}