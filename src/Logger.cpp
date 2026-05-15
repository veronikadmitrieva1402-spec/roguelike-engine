#define _CRT_SECURE_NO_WARNINGS
#include "../include/Logger.h"
#include <iostream>
#include <chrono>
#include <ctime>

Logger::Logger() {
    logFile.open("game.log", std::ios::app);
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::log(const std::string& message) {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    
    std::string logMsg = std::ctime(&time);
    logMsg.pop_back();
    logMsg += " | " + message;
    
    std::cout << "[LOG] " << logMsg << std::endl;
    if (logFile.is_open()) {
        logFile << logMsg << std::endl;
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

