#pragma once
#include <string>

class JsonParser {
public:
    static bool validatePlayerJson(const std::string& filePath);
    static bool validateEnemiesJson(const std::string& filePath);
    static bool validateItemsJson(const std::string& filePath);
};