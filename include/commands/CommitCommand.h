#pragma once

#include "commands/ICommand.h"

class CommitCommand : public ICommand{
public:
    void execute() override;
};