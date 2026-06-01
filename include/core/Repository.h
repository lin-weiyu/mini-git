#pragma once

#include <filesystem>

class Repository{
public:
    bool exists() const;

    bool init();

private:
    void createDirectories();
    void initializeHead();

private:
    const std::filesystem::path repoPath = ".mygit";
};

