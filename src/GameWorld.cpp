#include "../include/GameWorld.h"
#include "../include/Enemy.h"
#include "../include/Item.h"
#include "../include/Player.h"
#include "../include/Logger.h"
#include "../build/_deps/json-src/include/nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <queue>

using json = nlohmann::json;

GameWorld::GameWorld() : width(0), height(0) {}

GameWorld& GameWorld::getInstance() {
    static GameWorld instance;
    return instance;
}

GameWorld::~GameWorld() {
    for (auto e : enemies) delete e;
    for (auto i : items) delete i;
}

bool GameWorld::loadMap(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        Logger::getInstance().log("Ошибка загрузки карты: " + filePath);
        return false;
    }

    for (auto e : enemies) delete e;
    for (auto i : items) delete i;
    for (auto t : enemyTemplates) delete t;
    for (auto t : itemTemplates) delete t;
    enemies.clear();
    items.clear();
    enemyTemplates.clear();
    itemTemplates.clear();
    itemPositions.clear();
    
    map.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        map.push_back(line);
    }
    
    if (map.empty()) return false;

    height = static_cast<int>(map.size());
    width = static_cast<int>(map[0].size());
    
    Logger::getInstance().log("Карта загружена: " + std::to_string(width) + "x" + std::to_string(height));
    return true;
}

bool GameWorld::isWalkable(int x, int y) const {
    if (y < 0 || y >= static_cast<int>(map.size())) return false;
    if (x < 0 || x >= static_cast<int>(map[y].size())) return false;
    return map[y][x] != '#';
}

void GameWorld::display() const {
    Player& p = Player::getInstance();
    Position playerPos = p.getPosition();
    
    for (int y = 0; y < static_cast<int>(map.size()); ++y) {
        for (int x = 0; x < static_cast<int>(map[y].size()); ++x) {
            if (x == playerPos.x && y == playerPos.y) {
                std::cout << '@';
            } else {
                std::cout << map[y][x];
            }
        }
        std::cout << std::endl;
    }
}

char GameWorld::getTile(int x, int y) const {
    if (y < 0 || y >= static_cast<int>(map.size())) return '#';
    if (x < 0 || x >= static_cast<int>(map[y].size())) return '#';
    return map[y][x];
}

int GameWorld::getWidth() const { return width; }
int GameWorld::getHeight() const { return height; }

Enemy* GameWorld::getEnemyAt(int x, int y) {
    for (auto& enemy : enemies) {
        if (enemy->getPosition().x == x && enemy->getPosition().y == y && enemy->isAlive()) {
            return enemy;
        }
    }
    return nullptr;
}

void GameWorld::removeEnemy(int x, int y) {
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        if ((*it)->getPosition().x == x && (*it)->getPosition().y == y) {
            map[y][x] = '.';
            delete *it;
            enemies.erase(it);
            Logger::getInstance().log("Враг удалён с (" + std::to_string(x) + ", " + std::to_string(y) + ")");
            return;
        }
    }
}

Item* GameWorld::getItemAt(int x, int y) {
    for (size_t i = 0; i < itemPositions.size(); ++i) {
        if (itemPositions[i].x == x && itemPositions[i].y == y) {
            if (i < items.size()) {
                return items[i];
            }
        }
    }
    return nullptr;
}

void GameWorld::removeItem(int x, int y) {
    for (size_t i = 0; i < itemPositions.size(); ++i) {
        if (itemPositions[i].x == x && itemPositions[i].y == y) {
            map[y][x] = '.';
            if (i < items.size()) {
                delete items[i];
                items.erase(items.begin() + i);
            }
            itemPositions.erase(itemPositions.begin() + i);
            Logger::getInstance().log("Предмет поднят с (" + std::to_string(x) + ", " + std::to_string(y) + ")");
            return;
        }
    }
}

void GameWorld::loadEnemies(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        Logger::getInstance().log("Ошибка загрузки врагов: " + filePath);
        return;
    }
    
    json data = json::parse(file);
    enemyTemplates.clear();
    for (const auto& e : data) {
        Enemy* enemy = new Enemy(e["id"], e["name"], e["maxHP"], e["attack"], 
                                e["protection"], e["description"]);
        enemyTemplates.push_back(enemy);
    }
    Logger::getInstance().log("Загружено шаблонов врагов: " + std::to_string(enemyTemplates.size()));
}

void GameWorld::loadItems(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        Logger::getInstance().log("Ошибка загрузки предметов: " + filePath);
        return;
    }
    
    json data = json::parse(file);
    itemTemplates.clear();
    for (const auto& i : data) {
        Item* item = new Item(i["id"], i["name"], i["type"],
                            i["effect"]["type"], i["effect"]["value"], i["effect"]["description"]);
        itemTemplates.push_back(item);
    }
    Logger::getInstance().log("Загружено шаблонов предметов: " + std::to_string(itemTemplates.size()));
}

void GameWorld::spawnEntitiesFromMap() {
    int enemyIndex = 0;
    int itemIndex = 0;
    
    for (auto e : enemies) delete e;
    for (auto i : items) delete i;
    enemies.clear();
    items.clear();
    itemPositions.clear();

    int actualHeight = static_cast<int>(map.size());
    
    for (int y = 0; y < actualHeight; ++y) {
        int actualWidth = static_cast<int>(map[y].size());
        for (int x = 0; x < actualWidth; ++x) {
            if (map[y][x] == '?' && enemyIndex < static_cast<int>(enemyTemplates.size())) {
                Enemy* original = enemyTemplates[enemyIndex];
                Enemy* enemy = new Enemy(original->getId(), original->getName(), 
                                        original->getMaxHP(), original->getAttack(),
                                        original->getProtection(), original->getDescription());
                enemy->setPosition(x, y);
                enemies.push_back(enemy);
                enemyIndex++;
            }
            else if (map[y][x] == '+' && itemIndex < static_cast<int>(itemTemplates.size())) {
                Item* original = itemTemplates[itemIndex];
                Item* item = new Item(original->getId(), original->getName(), original->getType(),
                                    original->getEffectType(), original->getEffectValue(), original->getDescription());
                items.push_back(item);
                itemPositions.push_back({x, y});
                itemIndex++;
            }
        }
    }
    
    Logger::getInstance().log("Расставлено врагов: " + std::to_string(enemyIndex) + ", предметов: " + std::to_string(itemIndex));
}

bool GameWorld::isExit(int x, int y) const {
    if (y < 0 || y >= static_cast<int>(map.size())) return false;
    if (x < 0 || x >= static_cast<int>(map[y].size())) return false;
    return map[y][x] == '>';
}