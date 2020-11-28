#pragma once
#include "GEModule/IApplication.h"

namespace Rocket {
    class BaseApplication : implements IApplication
    {
    public:
        virtual int Initialize();
        virtual void Finalize();
        // One cycle of the main loop
        virtual void Tick();

        virtual bool IsQuit();

    protected:
        // Flag if need quit the main loop of the application
        bool m_bQuit;
    };
}