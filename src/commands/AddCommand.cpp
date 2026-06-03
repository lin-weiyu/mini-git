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

    std::filesystem::path source = args[0];

    if (!std::filesystem::exists(source)){
        std::cout << "File not found\n";
        return;
    }

    Repository repo;

    auto stagingDir = repo.getStagingPath();

    auto target = stagingDir / source.filename();

    std::filesystem::copy_file(
        source, target, std::filesystem::copy_options::overwrite_existing
    );

    std::cout << "Added " << source.filename().string() << "\n";
}