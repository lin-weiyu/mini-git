#include "commands/ICommand.h"
#include "commands/InitCommand.h"
#include "core/Repository.h"

#include <iostream>

void InitCommand::execute(){

    Repository repo;
    if (repo.init()){
        std::cout << "Repository initialized\n";
    }
    else{
        std::cout << "Repository already exists\n";
    }
}