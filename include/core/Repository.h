#pragma once

#include <filesystem>

class Repository{
public:
    bool exists() const;

    bool init();
    
    std::filesystem::path getStagingPath() const;
private:
    void createDirectories();
    void initializeHead();
    
private:
    const std::filesystem::path repoPath = ".mygit";
};

