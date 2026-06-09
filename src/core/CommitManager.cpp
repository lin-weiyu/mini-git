#include <iostream>
#include <string>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <sstream>
#include <fstream>

#include "core/CommitManager.h"

CommitManager::CommitManager(Repository& virtualrepo): repo(virtualrepo){
}

std::string CommitManager::getTime(){

    auto now = std::chrono::system_clock::now();

    auto time = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;

    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");

    std::string timestamp = ss.str();

    return timestamp;
}

bool CommitManager::createCommit(std::string content){

    if (!repo.exists()){
        std::cout << "not found .mygit\n";
        return false;
    }
    std::string head = repo.readHead();

    std::string nextId = std::to_string(std::stoi(head) + 1);

    std::filesystem::path currenthead = repo.getCommitsPath() / nextId;
    
    std::filesystem::create_directory(currenthead);
    
    int num = 0;
    for (const auto& entry : std::filesystem::directory_iterator(repo.getStagingPath())){
        if (entry.is_regular_file()){
            
            num++;
            
            auto target = currenthead / entry.path().filename();
            
            std::filesystem::copy(entry.path(), target, std::filesystem::copy_options::overwrite_existing);
        }
    }
    
    if (num == 0){
        std::filesystem::remove(currenthead);

        std::cout << "not found sraging files\n";
        
        return false;
    }


    std::ofstream meta(currenthead / "meta");

    meta << "id:" << nextId << "\n";

    meta << "parent:" << head << "\n";

    meta << "message:" << content << "\n";

    meta << "timestamp:" << getTime() << "\n";

    repo.updateHead(nextId);

    return true;
}