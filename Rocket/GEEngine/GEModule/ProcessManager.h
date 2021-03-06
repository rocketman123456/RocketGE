#pragma once
#include "GEInterface/IRuntimeModule.h"
#include "GEProcess/Process.h"

namespace Rocket
{
    class ProcessManager : implements IRuntimeModule
    {
    public:
        ProcessManager() : IRuntimeModule("ProcessManager") {}
        virtual ~ProcessManager() = default;

        virtual int Initialize() override;
        virtual void Finalize() override;

        virtual int Tick(Timestep ts) override;

        // interface
        uint64_t UpdateProcesses(unsigned long deltaMs);         // updates all attached processes
        WeakProcessPtr AttachProcess(StrongProcessPtr pProcess); // attaches a process to the process mgr
        void AbortAllProcesses(bool immediate);

        // accessors
        uint32_t GetProcessCount(void) const { return m_ProcessList.size(); }

    private:
        typedef std::list<StrongProcessPtr> ProcessList;
        ProcessList m_ProcessList;
    };

    extern ProcessManager *g_ProcessManager;
} // namespace Rocket