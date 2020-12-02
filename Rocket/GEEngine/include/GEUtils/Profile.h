/* Copyright (C) Steve Rabin, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Steve Rabin, 2000"
 */
#pragma once
#include "GECore/Core.h"
#include "GEInterface/Singleton.h"

#define NUM_PROFILE_SAMPLES 100

namespace Rocket {
    // TODO : shoule only use for profile
    class CustomTimer : implements Singleton <CustomTimer>
    {
    public:
        void InitTime(void);
        void MarkTimeThisTick(void);
        float GetElapsedTime(void);
        float GetExactTime(void);
    private:
        std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
        std::chrono::time_point<std::chrono::steady_clock> m_CurrentTimepoint;
        long long m_TimeLastTick;
    };

    typedef struct
    {
        bool bValid;                    //Whether this data is valid
        unsigned int iProfileInstances; //# of times ProfileBegin called
        int iOpenProfiles;              //# of times ProfileBegin w/o ProfileEnd
        //char szName[256];               //Name of sample
        std::string szName;
        float fStartTime;               //The current open profile start time
        float fAccumulator;             //All samples this frame added together
        float fChildrenSampleTime;      //Time taken by all children
        unsigned int iNumParents;       //Number of profile parents
    } ProfileSample;

    typedef struct
    {
        bool bValid;      //Whether the data is valid
        //char szName[256]; //Name of the sample
        std::string szName;
        float fAve;       //Average time per frame (percentage)
        float fMin;       //Minimum time per frame (percentage)
        float fMax;       //Maximum time per frame (percentage)
    } ProfileSampleHistory;

    class Profiler : implements Singleton<Profiler>
    {
    public:
        void ProfileInit(void);
        void ProfileBegin(char* name);
        void ProfileEnd(char* name);
        void ProfileDumpOutputToBuffer(void);

        const std::vector<std::string>& GetProfileInfo() { return m_ProfileInfo; }
    private:
        void StoreProfileInHistory(char* name, float percent);
        void GetProfileFromHistory(char* name, float *ave, float *min, float *max);
    private:
        std::vector<std::string>    m_ProfileInfo;
        ProfileSample               m_Samples[NUM_PROFILE_SAMPLES];
        ProfileSampleHistory        m_History[NUM_PROFILE_SAMPLES];
        float                       m_StartProfile = 0.0f;
        float                       m_EndProfile = 0.0f;
    };

    #define g_CustomTimer CustomTimer::GetSingleton()
    #define g_Profiler Profiler::GetSingleton()
}

