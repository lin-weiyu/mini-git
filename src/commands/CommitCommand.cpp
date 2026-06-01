#include "commands/ICommand.h"
#include "commands/CommitCommand.h"

#include <iostream>

void CommitCommand::execute(){
    std::cout << "commit command\n";
}