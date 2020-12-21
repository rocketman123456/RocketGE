
/* Copyright (C) Steve Rabin, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Steve Rabin, 2000"
 */
#include "GEUtils/Profile.h"

namespace Rocket
{
    void ProfilerTimer::InitTime()
    {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
        m_CurrentTimepoint = std::chrono::high_resolution_clock::now();
        m_TimeLastTick = 1000;
    }

    void ProfilerTimer::MarkTimeThisTick()
    {
        std::chrono::time_point<std::chrono::steady_clock> current;
        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_CurrentTimepoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(current).time_since_epoch().count();

        m_TimeLastTick = end - start;
        m_CurrentTimepoint = current;

        if (m_TimeLastTick <= 10)
            m_TimeLastTick = 10;
    }

    float ProfilerTimer::GetElapsedTime(void)
    {
        float duration = (m_TimeLastTick)*0.001f;
        return duration;
    }

    float ProfilerTimer::GetExactTime(void)
    {
        m_CurrentTimepoint = std::chrono::high_resolution_clock::now();
        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(m_CurrentTimepoint).time_since_epoch().count();

        float duration = (end - start) * 0.001f;
        return duration;
    }
} // namespace Rocket

namespace Rocket
{
    void Profiler::ProfileInit(void)
    {
        m_Timer.InitTime();

        for (uint32_t i = 0; i < NUM_PROFILE_SAMPLES; i++)
        {
            m_Samples[i].bValid = false;
            m_History[i].bValid = false;
        }
        m_StartProfile = m_Timer.GetExactTime();
        m_ProfileInfoVec.clear();
    }

    void Profiler::ProfileBegin(const std::string &name)
    {
        uint32_t i = 0;

        while (i < NUM_PROFILE_SAMPLES && m_Samples[i].bValid == true)
        {
            if (m_Samples[i].szName.compare(name) == 0)
            {
                //Found the sample
                m_Samples[i].iOpenProfiles++;
                m_Samples[i].iProfileInstances++;
                m_Samples[i].fStartTime = m_Timer.GetExactTime();
                assert(m_Samples[i].iOpenProfiles == 1); //max 1 open at once
                return;
            }
            i++;
        }

        if (i >= NUM_PROFILE_SAMPLES)
        {
            RK_CORE_ASSERT(false, "Exceeded Max Available Profile Samples");
            return;
        }

        m_Samples[i].szName = name;
        m_Samples[i].bValid = true;
        m_Samples[i].iOpenProfiles = 1;
        m_Samples[i].iProfileInstances = 1;
        m_Samples[i].fAccumulator = 0.0f;
        m_Samples[i].fStartTime = m_Timer.GetExactTime();
        m_Samples[i].fChildrenSampleTime = 0.0f;
    }

    void Profiler::ProfileEnd(const std::string &name)
    {
        uint32_t i = 0;
        uint32_t numParents = 0;

        while (i < NUM_PROFILE_SAMPLES && m_Samples[i].bValid == true)
        {
            if (m_Samples[i].szName.compare(name) == 0)
            { //Found the sample
                uint32_t inner = 0;
                int parent = -1;
                float fEndTime = m_Timer.GetExactTime();
                m_Samples[i].iOpenProfiles--;

                //Count all parents and find the immediate parent
                while (m_Samples[inner].bValid == true)
                {
                    if (m_Samples[inner].iOpenProfiles > 0)
                    { //Found a parent (any open profiles are parents)
                        numParents++;
                        if (parent < 0)
                        { //Replace invalid parent (index)
                            parent = inner;
                        }
                        else if (m_Samples[inner].fStartTime >=
                                 m_Samples[parent].fStartTime)
                        { //Replace with more immediate parent
                            parent = inner;
                        }
                    }
                    inner++;
                }

                //Remember the current number of parents of the sample
                m_Samples[i].iNumParents = numParents;

                if (parent >= 0)
                { //Record this time in fChildrenSampleTime (add it in)
                    m_Samples[parent].fChildrenSampleTime += fEndTime - m_Samples[i].fStartTime;
                }

                //Save sample time in accumulator
                m_Samples[i].fAccumulator += fEndTime - m_Samples[i].fStartTime;
                return;
            }
            i++;
        }
    }

    void Profiler::ProfileDumpOutputToBuffer(void)
    {
        m_Timer.MarkTimeThisTick();

        uint32_t i = 0;

        m_EndProfile = m_Timer.GetExactTime();
        m_ProfileInfoVec.clear();

        while (i < NUM_PROFILE_SAMPLES && m_Samples[i].bValid == true)
        {
            float sampleTime, percentTime, aveTime, minTime, maxTime;
            char indentedName[256], name[256];

            if (m_Samples[i].iOpenProfiles < 0)
            {
                RK_CORE_ASSERT(false, "ProfileEnd() called without a ProfileBegin()");
            }
            else if (m_Samples[i].iOpenProfiles > 0)
            {
                RK_CORE_ASSERT(false, "ProfileBegin() called without a ProfileEnd()");
            }

            sampleTime = m_Samples[i].fAccumulator - m_Samples[i].fChildrenSampleTime;
            percentTime = (sampleTime / (m_EndProfile - m_StartProfile)) * 100.0f;

            aveTime = minTime = maxTime = percentTime;

            //Add new measurement into the history and get the ave, min, and max
            StoreProfileInHistory(m_Samples[i].szName, percentTime);
            GetProfileFromHistory(m_Samples[i].szName, &aveTime, &minTime, &maxTime);

            uint32_t indent = 0;
            strcpy(indentedName, m_Samples[i].szName.c_str());
            for (indent = 0; indent < m_Samples[i].iNumParents; indent++)
            {
                sprintf(name, "    %s", indentedName);
                strcpy(indentedName, name);
            }

            m_ProfileInfoVec.push_back({indentedName,
                                        aveTime, minTime, maxTime,
                                        m_Samples[i].iProfileInstances,
                                        m_Samples[i].iNumParents});
            i++;
        }

        { //Reset samples for next frame
            uint32_t i;
            for (i = 0; i < NUM_PROFILE_SAMPLES; i++)
            {
                m_Samples[i].bValid = false;
            }
            m_StartProfile = m_Timer.GetExactTime();
        }
    }

    void Profiler::StoreProfileInHistory(const std::string &name, float percent)
    {
        uint32_t i = 0;
        float oldRatio;
        float newRatio = 0.8f * m_Timer.GetElapsedTime();
        if (newRatio > 1.0f)
        {
            newRatio = 1.0f;
        }
        oldRatio = 1.0f - newRatio;

        while (i < NUM_PROFILE_SAMPLES && m_History[i].bValid == true)
        {
            if (m_Samples[i].szName.compare(name) == 0)
            { //Found the sample
                m_History[i].fAve = (m_History[i].fAve * oldRatio) + (percent * newRatio);
                if (percent < m_History[i].fMin)
                {
                    m_History[i].fMin = percent;
                }
                else
                {
                    m_History[i].fMin = (m_History[i].fMin * oldRatio) + (percent * newRatio);
                }

                if (m_History[i].fMin < 0.0f)
                {
                    m_History[i].fMin = 0.0f;
                }

                if (percent > m_History[i].fMax)
                {
                    m_History[i].fMax = percent;
                }
                else
                {
                    m_History[i].fMax = (m_History[i].fMax * oldRatio) + (percent * newRatio);
                }
                return;
            }
            i++;
        }

        if (i < NUM_PROFILE_SAMPLES)
        { //Add to history
            m_History[i].szName = name;
            m_History[i].bValid = true;
            m_History[i].fAve = m_History[i].fMin = m_History[i].fMax = percent;
        }
        else
        {
            RK_CORE_ASSERT(false, "Exceeded Max Available Profile Samples!");
        }
    }

    void Profiler::GetProfileFromHistory(const std::string &name, float *ave, float *min, float *max)
    {
        uint32_t i = 0;
        while (i < NUM_PROFILE_SAMPLES && m_History[i].bValid == true)
        {
            if (m_Samples[i].szName.compare(name) == 0)
            { //Found the sample
                *ave = m_History[i].fAve;
                *min = m_History[i].fMin;
                *max = m_History[i].fMax;
                return;
            }
            i++;
        }
        *ave = *min = *max = 0.0f;
    }
} // namespace Rocket
