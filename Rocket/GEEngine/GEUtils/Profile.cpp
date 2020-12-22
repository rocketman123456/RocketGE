
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
        int64_t start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        int64_t end = std::chrono::time_point_cast<std::chrono::microseconds>(m_CurrentTimepoint).time_since_epoch().count();

        float duration = (end - start) * 0.001f;
        return duration;
    }

    int64_t ProfilerTimer::GetExactTimeCount(void)
    {
        m_CurrentTimepoint = std::chrono::high_resolution_clock::now();
        int64_t start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        int64_t end = std::chrono::time_point_cast<std::chrono::microseconds>(m_CurrentTimepoint).time_since_epoch().count();

        int64_t duration = (end - start);
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

namespace Rocket
{
    ProfilerTimer g_Timer;
    /***************************************************************************************************
    **
    ** CProfileNode
    **
    ***************************************************************************************************/

    /***********************************************************************************************
     * INPUT:                                                                                      *
     * name - pointer to a static string which is the name of this profile node                    *
     * parent - parent pointer                                                                     *
     *                                                                                             *
     * WARNINGS:                                                                                   *
     * The name is assumed to be a static pointer, only the pointer is stored and compared for     *
     * efficiency reasons.                                                                         *
     *=============================================================================================*/
    CProfileNode::CProfileNode(const char *name, CProfileNode *parent) 
        : Name(name),
          TotalCalls(0),
          TotalTime(0),
          StartTime(0),
          RecursionCounter(0),
          Parent(parent),
          Child(NULL),
          Sibling(NULL)
    {
        Reset();
    }

    CProfileNode::~CProfileNode(void)
    {
        delete Child;
        delete Sibling;
    }

    /***********************************************************************************************
     * INPUT:                                                                                      *
     * name - static string pointer to the name of the node we are searching for                   *
     *                                                                                             *
     * WARNINGS:                                                                                   *
     * All profile names are assumed to be static strings so this function uses pointer compares   *
     * to find the named node.                                                                     *
     *=============================================================================================*/
    CProfileNode *CProfileNode::Get_Sub_Node(const char *name)
    {
        // Try to find this sub node
        CProfileNode *child = Child;
        while (child)
        {
            if (child->Name == name)
            {
                return child;
            }
            child = child->Sibling;
        }

        // We didn't find it, so add it
        CProfileNode *node = new CProfileNode(name, this);
        node->Sibling = Child;
        Child = node;
        return node;
    }

    void CProfileNode::Reset(void)
    {
        TotalCalls = 0;
        TotalTime = 0.0f;

        if (Child)
        {
            Child->Reset();
        }
        if (Sibling)
        {
            Sibling->Reset();
        }
    }

    void CProfileNode::Call(void)
    {
        TotalCalls++;
        if (RecursionCounter++ == 0)
        {
            StartTime = g_Timer.GetExactTimeCount();
            //Profile_Get_Ticks(&StartTime);
        }
    }

    bool CProfileNode::Return(void)
    {
        if (--RecursionCounter == 0 && TotalCalls != 0)
        {
            int64_t time = g_Timer.GetExactTimeCount();
            //Profile_Get_Ticks(&time);
            time -= StartTime;
            TotalTime += (float)time / g_Timer.GetTickRate();
        }
        return (RecursionCounter == 0);
    }

    /***************************************************************************************************
    **
    ** CProfileIterator
    **
    ***************************************************************************************************/
    CProfileIterator::CProfileIterator(CProfileNode *start)
    {
        CurrentParent = start;
        CurrentChild = CurrentParent->Get_Child();
    }

    void CProfileIterator::First(void)
    {
        CurrentChild = CurrentParent->Get_Child();
    }

    void CProfileIterator::Next(void)
    {
        CurrentChild = CurrentChild->Get_Sibling();
    }

    bool CProfileIterator::Is_Done(void)
    {
        return CurrentChild == NULL;
    }

    void CProfileIterator::Enter_Child(int index)
    {
        CurrentChild = CurrentParent->Get_Child();
        while ((CurrentChild != NULL) && (index != 0))
        {
            index--;
            CurrentChild = CurrentChild->Get_Sibling();
        }

        if (CurrentChild != NULL)
        {
            CurrentParent = CurrentChild;
            CurrentChild = CurrentParent->Get_Child();
        }
    }

    void CProfileIterator::Enter_Parent(void)
    {
        if (CurrentParent->Get_Parent() != NULL)
        {
            CurrentParent = CurrentParent->Get_Parent();
        }
        CurrentChild = CurrentParent->Get_Child();
    }

    /***************************************************************************************************
    **
    ** CProfileManager
    **
    ***************************************************************************************************/

    CProfileNode CProfileManager::Root("Root", NULL);
    CProfileNode *CProfileManager::CurrentNode = &CProfileManager::Root;
    int CProfileManager::FrameCounter = 0;
    int64_t CProfileManager::ResetTime = 0;
    std::vector<ProfileNodeInfo> CProfileManager::InfoList = {};

    /***********************************************************************************************
     * CProfileManager::Start_Profile -- Begin a named profile                                    *
     *                                                                                             *
     * Steps one level deeper into the tree, if a child already exists with the specified name     *
     * then it accumulates the profiling; otherwise a new child node is added to the profile tree. *
     *                                                                                             *
     * INPUT:                                                                                      *
     * name - name of this profiling record                                                        *
     *                                                                                             *
     * WARNINGS:                                                                                   *
     * The string used is assumed to be a static string; pointer compares are used throughout      *
     * the profiling code for efficiency.                                                          *
     *=============================================================================================*/
    void CProfileManager::Start_Profile(const char *name)
    {
        if (name != CurrentNode->Get_Name())
        {
            CurrentNode = CurrentNode->Get_Sub_Node(name);
        }

        CurrentNode->Call();
    }

    /***********************************************************************************************
     * CProfileManager::Stop_Profile -- Stop timing and record the results.                       *
     *=============================================================================================*/
    void CProfileManager::Stop_Profile(void)
    {
        // Return will indicate whether we should back up to our parent (we may
        // be profiling a recursive function)
        if (CurrentNode->Return())
        {
            CurrentNode = CurrentNode->Get_Parent();
        }
    }

    void CProfileManager::DumpProfileInfo()
    {
        //InfoList.clear();
        auto iter = CProfileManager::Get_Iterator();
        while(!iter->Is_Done())
        {

        }
        CProfileManager::Release_Iterator(iter);
    }

    /***********************************************************************************************
     * CProfileManager::Reset -- Reset the contents of the profiling system                       *
     *                                                                                             *
     *    This resets everything except for the tree structure.  All of the timing data is reset.  *
     *=============================================================================================*/
    void CProfileManager::Reset(void)
    {
        g_Timer.InitTime();
        Root.Reset();
        FrameCounter = 0;
        ResetTime = g_Timer.GetExactTimeCount();
        //Profile_Get_Ticks(&ResetTime);
    }

    /***********************************************************************************************
     * CProfileManager::Increment_Frame_Counter -- Increment the frame counter                    *
     *=============================================================================================*/
    void CProfileManager::Increment_Frame_Counter(void)
    {
        FrameCounter++;
    }

    /***********************************************************************************************
     * CProfileManager::Get_Time_Since_Reset -- returns the elapsed time since last reset         *
     *=============================================================================================*/
    float CProfileManager::Get_Time_Since_Reset(void)
    {
        int64_t time = g_Timer.GetExactTimeCount();
        //Profile_Get_Ticks(&time);
        time -= ResetTime;
        return (float)time / g_Timer.GetTickRate();
    }
} // namespace Rocket