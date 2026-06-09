#include <iostream>
#include <string>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <sstream>
#include <fstream>
#include <array>

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