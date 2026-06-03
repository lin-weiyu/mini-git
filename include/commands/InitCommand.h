#pragma once

#include <vector>
#include <string>

#include "commands/ICommand.h"

class InitCommand : public ICommand{
public:
    void execute(
        const std::vector<std::string>& args
    ) override;
};