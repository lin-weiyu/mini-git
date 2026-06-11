#include <vector>
#include <string>

#include "commands/ICommand.h"
#include "commands/CheckoutCommand.h"
#include "core/Repository.h"
#include "core/CommitManager.h"

void CheckoutCommand::execute(const std::vector<std::string>& args){
    if (args.empty()){
        std::cout << "Usage:mini-git checkout <ID>\n";
        return;
    }

    Repository repo;

    CommitManager manager(repo);

    if (!manager.checkout(args[0])){
        std::cout << "Checkout success.\n";
    }
    else{
        std::cout << "Checkout failure.\n";
    }
}