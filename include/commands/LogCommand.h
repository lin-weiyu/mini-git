#pragma once

#include <string>
#include <vector>

#include "commands/ICommand.h"

class LogCommand : public ICommand{
public:
    void execute(
        const std::vector<std::string>& args
    ) override; 
};