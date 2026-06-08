#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>

#include "core/Repository.h"

class CommitManager{
private:
    Repository& repo;
    std::string getTime();
public:
    CommitManager(Repository& virtualrepo);

    bool createCommit(std::string content);

};