#pragma once
#include "GEInterface/IApplication.h"

namespace Rocket
{
    class BaseApplication : implements IApplication
    {
    public:
        virtual int Initialize();
        virtual void Finalize();
        // One cycle of the main loop
        virtual int Tick(Timestep ts);

        virtual bool IsQuit();

    protected:
        // Flag if need quit the main loop of the application
        bool m_bQuit;
    };
} // namespace Rocket