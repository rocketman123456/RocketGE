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

namespace Rocket
{
    typedef struct
    {
        bool bValid;                //Whether this data is valid
        uint32_t iProfileInstances; //# of times ProfileBegin called
        int iOpenProfiles;          //# of times ProfileBegin w/o ProfileEnd
        //char szName[256];               //Name of sample
        std::string szName;
        float fStartTime;          //The current open profile start time
        float fAccumulator;        //All samples this frame added together
        float fChildrenSampleTime; //Time taken by all children
        uint32_t iNumParents;      //Number of profile parents
    } ProfileSample;

    typedef struct
    {
        bool bValid; //Whether the data is valid
        //char szName[256]; //Name of the sample
        std::string szName;
        float fAve; //Average time per frame (percentage)
        float fMin; //Minimum time per frame (percentage)
        float fMax; //Maximum time per frame (percentage)
    } ProfileSampleHistory;

    typedef struct
    {
        std::string szName;
        float fAve; //Average time per frame (percentage)
        float fMin; //Minimum time per frame (percentage)
        float fMax; //Maximum time per frame (percentage)
        uint32_t iNum;
        uint32_t iParent;
    } ProfileInfo;

    // this timer shoule only use for profile
    class ProfilerTimer : implements Singleton<ProfilerTimer>
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

    class Profiler : implements Singleton<Profiler>
    {
    public:
        void ProfileInit(void);
        void ProfileBegin(const std::string &name);
        void ProfileEnd(const std::string &name);
        void ProfileDumpOutputToBuffer(void);

        const std::vector<ProfileInfo> &GetProfileInfo() { return m_ProfileInfoVec; }

    private:
        void StoreProfileInHistory(const std::string &name, float percent);
        void GetProfileFromHistory(const std::string &name, float *ave, float *min, float *max);

    private:
        std::vector<ProfileInfo> m_ProfileInfoVec;
        ProfileSample m_Samples[NUM_PROFILE_SAMPLES];
        ProfileSampleHistory m_History[NUM_PROFILE_SAMPLES];
        float m_StartProfile = 0.0f;
        float m_EndProfile = 0.0f;
    };

//#define g_ProfilerTimer ProfilerTimer::GetSingleton()
//#define g_Profiler Profiler::GetSingleton()
#define ProfilerInit() Profiler::GetSingleton().ProfileInit()
#define ProfilerBegin(name) Profiler::GetSingleton().ProfileBegin(name)
#define ProfilerEnd(name) Profiler::GetSingleton().ProfileEnd(name)
#define ProfilerDump() Profiler::GetSingleton().ProfileDumpOutputToBuffer()
#define ProfilerGetInfo() Profiler::GetSingleton().GetProfileInfo()
} // namespace Rocket
