#pragma once

#include "commands/ICommand.h"

class AddCommand : public ICommand{
public:
    void execute() override;
};