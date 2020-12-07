#pragma once
#include "GEInterface/IRuntimeModule.h"
#include "GEProcess/Process.h"

namespace Rocket {
    class ProcessManager : implements IRuntimeModule
    {
    public:
        virtual int Initialize() override;
        virtual void Finalize() override;

        virtual void Tick(Timestep ts) override;

        // interface
        uint64_t UpdateProcesses(unsigned long deltaMs);  // updates all attached processes
        WeakProcessPtr AttachProcess(StrongProcessPtr pProcess);  // attaches a process to the process mgr
        void AbortAllProcesses(bool immediate);

        // accessors
        unsigned int GetProcessCount(void) const { return m_ProcessList.size(); }
    private:
        typedef std::list<StrongProcessPtr> ProcessList;
	    ProcessList m_ProcessList;
    };

    extern ProcessManager* g_ProcessManager;
}