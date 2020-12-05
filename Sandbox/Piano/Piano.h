#pragma once
#include "RKEngine.h"

namespace Rocket {
    class Piano : implements Application
    {
    public:
        virtual void PreInitialize() override;
        virtual void PostInitialize() override;
        virtual void PreInitializeModule() override;
        virtual void PostInitializeModule() override;
        private:
        AudioManager* m_AudioManager;
    };
}