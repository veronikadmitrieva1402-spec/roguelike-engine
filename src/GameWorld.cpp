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
    
    map.clear();
    std::string line;
    while (std::getline(file, line)) {
        map.push_back(line);
    }
    
    height = static_cast<int>(map.size());
    width = height > 0 ? static_cast<int>(map[0].size()) : 0;
    
    Logger::getInstance().log("Карта загружена: " + std::to_string(width) + "x" + std::to_string(height));
    return true;
}

bool GameWorld::isWalkable(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) return false;
    char tile = map[y][x];
    return tile != '#';
}

void GameWorld::display() const {
    Player& p = Player::getInstance();
    Position playerPos = p.getPosition();
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
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
    if (x < 0 || x >= width || y < 0 || y >= height) return '#';
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
    for (size_t i = 0; i < items.size(); ++i) {
        if (itemPositions[i].x == x && itemPositions[i].y == y) {
            return items[i];
        }
    }
    return nullptr;
}

void GameWorld::removeItem(int x, int y) {
    for (size_t i = 0; i < itemPositions.size(); ++i) {
        if (itemPositions[i].x == x && itemPositions[i].y == y) {
            map[y][x] = '.';
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
    
    itemPositions.clear();
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (map[y][x] == '?' && enemyIndex < static_cast<int>(enemyTemplates.size())) {
                Enemy* original = enemyTemplates[enemyIndex];
                Enemy* enemy = new Enemy(original->getId(), original->getName(), 
                                        original->getMaxHP(), original->getAttack(),
                                        original->getProtection(), "");
                enemy->setPosition(x, y);
                enemies.push_back(enemy);
                enemyIndex++;
                Logger::getInstance().log("Враг размещён: " + enemy->getName() + " на (" + std::to_string(x) + ", " + std::to_string(y) + ")");
            }
            else if (map[y][x] == '+' && itemIndex < static_cast<int>(itemTemplates.size())) {
                
                Item* original = itemTemplates[itemIndex];
                Item* item = new Item(original->getId(), original->getName(), original->getType(),
                                     original->getEffectType(), original->getEffectValue(), original->getDescription());
                items.push_back(item);
                itemPositions.push_back({x, y});
                itemIndex++;
                Logger::getInstance().log("Предмет размещён: " + item->getName() + " на (" + std::to_string(x) + ", " + std::to_string(y) + ")");
            }
        }
    }
    
    Logger::getInstance().log("Расставлено врагов: " + std::to_string(enemyIndex) + ", предметов: " + std::to_string(itemIndex));
}