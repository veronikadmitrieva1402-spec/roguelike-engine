#pragma once
#include <string>
#include <vector>

class MapLoader {
public:
    static std::vector<std::string> loadCSV(const std::string& filePath);
    static bool validateMap(const std::vector<std::string>& map);
};