#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

#include "commands/ICommand.h"
#include "commands/AddCommand.h"
#include "core/Repository.h"


void AddCommand::execute(
    const std::vector<std::string>& args
){
    if (args.empty()){
        std::cout << "Usage: mini-git add <file>\n";
        return;
    }

    for (auto& arg : args){
        std::filesystem::path source = arg;
    
        if (!std::filesystem::exists(source)){
            std::cout << "File not found\n";
            continue;
        }
        Repository repo;

        if (std::filesystem::is_regular_file(source)){
            std::filesystem::path entry = source;

            std::filesystem::path relative_path = std::filesystem::relative(entry, repo.getRootPath());
    
            auto target = repo.getStagingPath() / relative_path;

            std::filesystem::create_directories(target.parent_path());
    
            std::filesystem::copy(entry, target, std::filesystem::copy_options::overwrite_existing);
        }
        else{
            for (const auto& entry : std::filesystem::recursive_directory_iterator(source)){
                if (entry.path().string().find(".mygit") != std::string::npos) continue;
                if (entry.is_directory()){
                    continue;
                }
                else{
                    std::filesystem::path relative_path = std::filesystem::relative(entry.path(), repo.getRootPath());
    
                    auto target = repo.getStagingPath() / relative_path;

                    std::filesystem::create_directories(target.parent_path());
    
                    std::filesystem::copy(entry.path(), target, std::filesystem::copy_options::overwrite_existing);
                }
            }
        }

        std::cout << "Added " << source.filename().string() << "\n";
    }
}