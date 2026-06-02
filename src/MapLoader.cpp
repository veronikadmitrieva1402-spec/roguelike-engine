#include "MapLoader.h"
#include "Logger.h"
#include <fstream>

std::vector<std::string> MapLoader::loadCSV(const std::string& filePath) {
    std::vector<std::string> map;
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        Logger::getInstance().log("Ошибка: не удалось открыть карту " + filePath);
        return map;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        map.push_back(line);
    }
    
    Logger::getInstance().log("Карта загружена: " + std::to_string(map[0].size()) + "x" + std::to_string(map.size()));
    return map;
}

bool MapLoader::validateMap(const std::vector<std::string>& map) {
    if (map.empty()) return false;
    
    size_t width = map[0].size();
    for (const auto& row : map) {
        if (row.size() != width) return false;
    }
    return true;
}