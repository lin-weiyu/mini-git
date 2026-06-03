#include "core/Repository.h"
#include <fstream>

bool Repository::exists() const{
    return std::filesystem::exists(repoPath);
}

void Repository::createDirectories(){

    std::filesystem::create_directory(repoPath);

    std::filesystem::create_directory(
        repoPath / "commits"
    );

    std::filesystem::create_directory(
        repoPath / "staging"
    );
}

void Repository::initializeHead(){
    std::ofstream head(
        repoPath / "HEAD"
    );

    head << "0";
}

bool Repository::init(){
    if (exists()){
        return false;
    }

    createDirectories();

    initializeHead();
    
    return true;
}

std::filesystem::path Repository::getStagingPath() const{
    return repoPath / "staging";
}