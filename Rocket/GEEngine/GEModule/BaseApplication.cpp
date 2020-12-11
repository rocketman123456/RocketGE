#include "GEModule/BaseApplication.h"

namespace Rocket {
    // Parse command line, read configuration, initialize all sub modules
    int BaseApplication::Initialize()
    {
        m_bQuit = false;
        return 0;
    }

    // Finalize all sub modules and clean up all runtime temporary files.
    void BaseApplication::Finalize()
    {
    }

    // One cycle of the main loop
    int BaseApplication::Tick(Timestep ts)
    {
        return 0;
    }

    bool BaseApplication::IsQuit()
    {
        return m_bQuit;
    }
}