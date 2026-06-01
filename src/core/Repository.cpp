#include "core/Repository.h"

bool Repository::exists() const{
    return std::filesystem::exists(repoPath);
}

bool Repository::init(){
    if (exists()){
        return false;
    }
    
    std::filesystem::create_directory(repoPath);

    return true;
}