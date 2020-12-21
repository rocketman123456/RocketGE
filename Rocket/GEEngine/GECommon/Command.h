#pragma once
#include "GECore/Core.h"

namespace Rocket
{
    // TODO : use command pattern to execute different type
    Interface Command
    {
    public:
        virtual ~Command() {}
        virtual void Execute() = 0;
    };
    //Command* command = inputHandler.handleInput();
    //if (command)
    //{
    //    command->execute(actor);
    //}
} // namespace Rocket
