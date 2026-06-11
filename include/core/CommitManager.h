#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <array>
#include <vector>
#include <string>

#include "core/Repository.h"

typedef std::array<std::string, 4> MetaData;

class CommitManager{
private:
    Repository& repo;

    std::string getTime();

public:
    const int Metadata_id = 0, Metadata_parent = 1, Metadata_message = 2, Metadata_date = 3;
    
    CommitManager(Repository& virtualrepo);

    bool createCommit(std::string content);

    std::vector<MetaData> getCommitHistory();

    void logCommit();

    bool checkout(std::string targetId);
};