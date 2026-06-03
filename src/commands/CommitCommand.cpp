#include <iostream>
#include <vector>
#include <string>

#include "commands/ICommand.h"
#include "commands/CommitCommand.h"


void CommitCommand::execute(
    const std::vector<std::string>& args
){
    std::cout << "commit command\n";
}