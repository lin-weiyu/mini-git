#include <iostream>
#include <vector>
#include <string>

#include "commands/ICommand.h"
#include "commands/CommitCommand.h"
#include "core/CommitManager.h"
#include "core/Repository.h"

void CommitCommand::execute(
    const std::vector<std::string>& args
){
    if (args.empty()){
        std::cout << "Usage: mini-git commit -m <message>\n";

        return;
    }

    std::string argument = args[0];

    if (argument != "-m"){
        std::cout << "argument failure\n";

        return;
    }
    std::string content = args[1];

    Repository repo;


    CommitManager commitManager(repo);

    if (commitManager.createCommit(content)){
        std::cout << "Commit success\n";
    }
    else{
        std::cout << "Commit failure\n";
    }
}