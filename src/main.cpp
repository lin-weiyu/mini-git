#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "commands/InitCommand.h"
#include "commands/AddCommand.h"
#include "commands/CommitCommand.h"

int main(int argc, char* argv[]){

    if (argc < 2){
        std::cout << "Usage: mini-git <command>\n";
        return 1;
    }

    std::string command = argv[1];

    std::unique_ptr<ICommand> cmd;

    if (command == "init"){
        cmd = std::make_unique<InitCommand>();
    }
    else if (command == "add"){
        cmd = std::make_unique<AddCommand>();
    }
    else if (command == "commit"){
        cmd = std::make_unique<CommitCommand>();
    }
    else{
        std::cout << "Unknow command\n";
        return 1;
    }

    std::vector<std::string> args;
    
    for (int i = 2; i < argc; i++){
        args.push_back(argv[i]);
    }

    cmd->execute(args);

    return 0;
}