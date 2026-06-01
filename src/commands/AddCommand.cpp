#include "commands/ICommand.h"
#include "commands/AddCommand.h"

#include <iostream>

void AddCommand::execute(){
    std::cout << "add command\n";
}