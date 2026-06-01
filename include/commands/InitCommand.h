#pragma once

#include "commands/ICommand.h"

class InitCommand : public ICommand{
public:
    void execute() override;
}