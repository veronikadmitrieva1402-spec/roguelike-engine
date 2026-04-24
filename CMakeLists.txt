cmake_minimum_required(VERSION 3.10)
project(RoguelikeEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/Entity.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/Item.cpp
    src/GameWorld.cpp
    src/MapLoader.cpp
    src/JsonParser.cpp
    src/Logger.cpp
)

set(HEADERS
    include/Entity.h
    include/Player.h
    include/Enemy.h
    include/Item.h
    include/GameWorld.h
    include/MapLoader.h
    include/JsonParser.h
    include/Logger.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE include)

find_package(nlohmann_json 3.10.0 QUIET)
if(nlohmann_json_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
    target_compile_definitions(${PROJECT_NAME} PRIVATE USE_NLOHMANN_JSON)
else()
    message(STATUS "nlohmann_json not found via find_package, trying FetchContent...")
    include(FetchContent)
    FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
    )
    FetchContent_MakeAvailable(json)
    target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()