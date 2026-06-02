#include "JsonParser.h"
#include "Logger.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

bool JsonParser::validatePlayerJson(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) return false;
    
    try {
        json data = json::parse(file);
        if (!data.contains("name") || !data.contains("maxHP") || 
            !data.contains("attack") || !data.contains("protection")) {
            return false;
        }
        return true;
    } catch (...) {
        return false;
    }
}

bool JsonParser::validateEnemiesJson(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) return false;
    
    try {
        json data = json::parse(file);
        return data.is_array();
    } catch (...) {
        return false;
    }
}

bool JsonParser::validateItemsJson(const std::string& filePath) {
    return validateEnemiesJson(filePath);
}