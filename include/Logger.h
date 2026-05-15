#pragma once 
#include <string>
#include <fstream>

class Logger {
private:
    std::ofstream logFile;
    Logger();
public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstance();
    void log(const std::string& message);
    ~Logger();
};