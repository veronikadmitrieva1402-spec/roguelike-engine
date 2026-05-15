include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.7.1
)
FetchContent_MakeAvailable(Catch2)

set(TEST_SOURCES
    ${CMAKE_SOURCE_DIR}/src/Entity.cpp
    ${CMAKE_SOURCE_DIR}/src/Player.cpp
    ${CMAKE_SOURCE_DIR}/src/Enemy.cpp
    ${CMAKE_SOURCE_DIR}/src/Item.cpp
    ${CMAKE_SOURCE_DIR}/src/GameWorld.cpp
    ${CMAKE_SOURCE_DIR}/src/Logger.cpp
    ${CMAKE_SOURCE_DIR}/src/MapLoader.cpp
    ${CMAKE_SOURCE_DIR}/src/JsonParser.cpp
)

add_executable(test_entity test_entity.cpp ${TEST_SOURCES})
target_include_directories(test_entity PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_entity PRIVATE Catch2::Catch2WithMain nlohmann_json::nlohmann_json)

add_executable(test_player test_player.cpp ${TEST_SOURCES})
target_include_directories(test_player PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_player PRIVATE Catch2::Catch2WithMain nlohmann_json::nlohmann_json)

add_executable(test_enemy test_enemy.cpp ${TEST_SOURCES})
target_include_directories(test_enemy PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_enemy PRIVATE Catch2::Catch2WithMain nlohmann_json::nlohmann_json)

add_executable(test_item test_item.cpp ${TEST_SOURCES})
target_include_directories(test_item PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_item PRIVATE Catch2::Catch2WithMain nlohmann_json::nlohmann_json)

add_executable(test_gameworld test_gameworld.cpp ${TEST_SOURCES})
target_include_directories(test_gameworld PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_gameworld PRIVATE Catch2::Catch2WithMain nlohmann_json::nlohmann_json)

add_executable(test_logger test_logger.cpp ${TEST_SOURCES})
target_include_directories(test_logger PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_logger PRIVATE Catch2::Catch2WithMain nlohmann_json::nlohmann_json)

add_executable(test_scenarios test_scenarios.cpp ${TEST_SOURCES})
target_include_directories(test_scenarios PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_scenarios PRIVATE Catch2::Catch2WithMain nlohmann_json::nlohmann_json)

add_test(NAME EntityTests COMMAND test_entity)
add_test(NAME PlayerTests COMMAND test_player)
add_test(NAME EnemyTests COMMAND test_enemy)
add_test(NAME ItemTests COMMAND test_item)
add_test(NAME GameWorldTests COMMAND test_gameworld)
add_test(NAME LoggerTests COMMAND test_logger)
add_test(NAME ScenarioTests COMMAND test_scenarios)