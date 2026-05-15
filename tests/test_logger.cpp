#include <catch2/catch_test_macros.hpp>
#include "../include/Logger.h"
#include <fstream>

TEST_CASE("Logger singleton", "[logger]") {
    Logger& log1 = Logger::getInstance();
    Logger& log2 = Logger::getInstance();
    
    SECTION("Same instance") {
        REQUIRE(&log1 == &log2);
    }
    
    SECTION("Log does not crash") {
        REQUIRE_NOTHROW(log1.log("Test message"));
    }
    
    SECTION("Log with empty message") {
        REQUIRE_NOTHROW(log1.log(""));
    }
    
    SECTION("Log with special characters") {
        REQUIRE_NOTHROW(log1.log("!@#$%^&*()"));
    }
    
    SECTION("Log with numbers") {
        REQUIRE_NOTHROW(log1.log("Damage: 42"));
    }
    
    SECTION("Multiple logs") {
        REQUIRE_NOTHROW(log1.log("One"));
        REQUIRE_NOTHROW(log1.log("Two"));
        REQUIRE_NOTHROW(log1.log("Three"));
    }
}