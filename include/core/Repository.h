#pragma once

#include <filesystem>

class Repository{
public:
    bool exists() const;

    bool init();

private:
    const std::filesystem::path repoPath = ".mygit";
};

