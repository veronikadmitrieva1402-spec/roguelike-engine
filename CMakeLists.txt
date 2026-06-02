cmake_minimum_required(VERSION 3.10)
project(RoguelikeEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_INSTALL_RPATH "$ORIGIN")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
endif()

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

include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/mods
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/mods
)

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()