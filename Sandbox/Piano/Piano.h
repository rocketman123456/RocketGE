#pragma once
#include "RKEngine.h"

namespace Rocket {
    class Piano : implements Application
    {
    public:
        virtual int Initialize() override;
        virtual int InitializeModule() override;
        private:
        AudioManager* m_AudioManager;
    };
}