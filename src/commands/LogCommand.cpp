#include <string>
#include <vector>

#include "core/Repository.h"
#include "core/CommitManager.h"
#include "commands/LogCommand.h"

void LogCommand::execute(const std::vector<std::string>& args){
    Repository repo;

    CommitManager commitManager(repo);

    commitManager.logCommit();
}