#include <iostream>
#include <vector>
#include <string>

#include "commands/ICommand.h"
#include "commands/InitCommand.h"
#include "core/Repository.h"


void InitCommand::execute(
    const std::vector<std::string>& args
){

    Repository repo;
    if (repo.init()){
        std::cout << "Repository initialized\n";
    }
    else{
        std::cout << "Repository already exists\n";
    }
}