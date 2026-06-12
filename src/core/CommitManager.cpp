#include <iostream>
#include <string>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <sstream>
#include <fstream>
#include <array>
#include <unordered_set>
#include <algorithm>

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
    
    int maxId = 0;
    
    for (const auto& entry: std::filesystem ::directory_iterator(repo.getCommitsPath())){
        if (entry.is_directory()){
            int id = std::stoi(entry.path().filename().string());

            if (id > maxId) maxId = id;
        }
    }

    std::string head = repo.readHead();

    std::string nextId = std::to_string(maxId + 1);

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

    std::string currentTime = getTime();

    meta << "id:" << nextId << "\n";

    meta << "parent:" << head << "\n";

    meta << "message:" << content << "\n";

    meta << "timestamp:" << currentTime << "\n";

    repo.updateHead(nextId);

    std::cout << "id:" << nextId << "\n";

    std::cout << "message:" << content << "\n";

    std::cout << "timestamp:" << currentTime << "\n";

    return true;
}


std::vector<MetaData> CommitManager::getCommitHistory(){
    std::string currentId = repo.readHead();
    
    std::vector<MetaData> datas;

    if (currentId == "0"){
        return datas;
    }

    while (currentId != "0"){
        std::filesystem::path meta = repo.getCommitsPath() / currentId  / "meta";

        std::ifstream metafile(meta);

        std::string line, key, value;
        
        MetaData data;

        while (getline(metafile, line)){
            size_t pos = line.find(":");
            
            key = line.substr(0, pos);

            value = line.substr(pos + 1);

            if (key == "id") data[Metadata_id] = value;
            else if (key == "parent") data[Metadata_parent] = value;
            else if (key == "message") data[Metadata_message] = value;
            else if (key == "timestamp") data[Metadata_date] = value;

        }
        datas.push_back(data);

        currentId = data[Metadata_parent];
    }

    std::reverse(datas.begin(), datas.end());

    return datas;
}


void CommitManager::logCommit(){
    std::vector<MetaData> datas = getCommitHistory();

    if (datas.empty()){
        std::cout << "Not commit yet.\n";

        return;
    }

    for (const MetaData& data : datas){
        std::cout << "id: " << data[Metadata_id] << "\n";

        std::cout << "parent: " << data[Metadata_parent] << "\n";

        std::cout << "message: " << data[Metadata_message] << "\n";

        std::cout << "date: " << data[Metadata_date] << "\n";

        std::cout << "\n";
    }
}

bool CommitManager::checkout(std::string targetId){

    if (!repo.exists()){
        std::cout << "Not initialized.\n";
        return false;
    }

    int targetId_exit = 0;

    for (const auto& entry : std::filesystem::directory_iterator(repo.getCommitsPath())){
        if (entry.is_directory()){

            std::string Id = entry.path().filename().string();

            if (Id == targetId){
                targetId_exit = 1;
                break;
            }
        }
    }

    if (!targetId_exit){
        std::cout << "Id was not found.\n";
        return false;
    }

    repo.updateHead(targetId);

    std::string currentId = targetId;

    std::unordered_set<std::string> tracked;

    std::filesystem::path targetPath = repo.getRootPath();

    std::filesystem::path sources = repo.getCommitsPath();

    while (currentId != "0"){
        std::filesystem::path currentCommitPath = sources / currentId;

        for (const auto& entry : std::filesystem::directory_iterator(currentCommitPath)){

            std::string currentFileName = entry.path().filename();

            if (currentFileName == "meta") continue;

            if (tracked.find(currentFileName) != tracked.end()) continue;

            std::filesystem::copy(currentCommitPath / currentFileName, targetPath / currentFileName, std::filesystem::copy_options::overwrite_existing);

            tracked.insert(currentFileName);
        }

        std::ifstream meta(currentCommitPath / "meta");

        std::string Id, parent;

        std::getline(meta, Id);

        std::getline(meta, parent);

        int pos = parent.find(":");

        parent = parent.substr(pos + 1);

        currentId = parent;
    }

    return true;
}