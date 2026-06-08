#pragma once

#include <filesystem>
#include <string>

class Repository{
public:
    bool exists() const;

    bool init();
    
    std::filesystem::path getStagingPath() const;

    std::string readHead() const;

    std::filesystem::path getCommitsPath() const;

    void updateHead(std::string commitId);
private:
    void createDirectories();
    void initializeHead();
    
private:
    const std::filesystem::path repoPath = ".mygit";
};

