#include "commands/ICommand.h"
#include "commands/InitCommand.h"

#include <iostream>

void InitCommand::execute(){
    std::cout << "Init command\n";
}