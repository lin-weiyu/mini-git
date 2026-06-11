#include "core/Repository.h"
#include <fstream>
#include <string>
#include <iostream>

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

std::string Repository::readHead() const{

    if (!std::filesystem::exists(repoPath / "HEAD")){
        std::cout << "HEAD file not found.";
        return "";
    }

    std::ifstream file(repoPath / "HEAD");

    std::string content;

    std::getline(file, content);

    return content;
}

void Repository::updateHead(std::string commitId){
    std::string context = commitId;

    std::ofstream file(repoPath / "HEAD");

    file << context;

}

std::filesystem::path Repository::getCommitsPath() const{
    return repoPath / "commits";
}

std::filesystem::path Repository::getRootPath() const{
    auto parent = repoPath.parent_path();
    return parent.empty() ? "." : parent;
}