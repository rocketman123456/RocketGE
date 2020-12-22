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
#include "GEUtils/Timer.h"

#define NUM_PROFILE_SAMPLES 1000

namespace Rocket
{
    typedef struct
    {
        bool bValid;                //Whether this data is valid
        uint32_t iProfileInstances; //# of times ProfileBegin called
        int iOpenProfiles;          //# of times ProfileBegin w/o ProfileEnd
        std::string szName;        //Name of sample
        float fStartTime;          //The current open profile start time
        float fAccumulator;        //All samples this frame added together
        float fChildrenSampleTime; //Time taken by all children
        uint32_t iNumParents;      //Number of profile parents
    } ProfileSample;

    typedef struct
    {
        bool bValid; //Whether the data is valid
        std::string szName; //Name of the sample
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
        ProfilerTimer m_Timer;
        std::vector<ProfileInfo> m_ProfileInfoVec;
        ProfileSample m_Samples[NUM_PROFILE_SAMPLES];
        ProfileSampleHistory m_History[NUM_PROFILE_SAMPLES];
        float m_StartProfile = 0.0f;
        float m_EndProfile = 0.0f;
    };
#ifdef RK_DEBUG
#define ProfilerInit() Profiler::GetSingleton().ProfileInit()
#define ProfilerBegin(name) Profiler::GetSingleton().ProfileBegin(name)
#define ProfilerEnd(name) Profiler::GetSingleton().ProfileEnd(name)
#define ProfilerDump() Profiler::GetSingleton().ProfileDumpOutputToBuffer()
#define ProfilerGetInfo() Profiler::GetSingleton().GetProfileInfo()
#else
#define ProfilerInit()
#define ProfilerBegin(name)
#define ProfilerEnd(name)
#define ProfilerDump()
#define ProfilerGetInfo()
#endif
} // namespace Rocket

namespace Rocket
{
    // A node in the Profile Hierarchy Tree
    class CProfileNode
    {

    public:
        CProfileNode(const char *name, CProfileNode *parent);
        ~CProfileNode(void);

        CProfileNode *Get_Sub_Node(const char *name);

        CProfileNode *Get_Parent(void) { return Parent; }
        CProfileNode *Get_Sibling(void) { return Sibling; }
        CProfileNode *Get_Child(void) { return Child; }

        void Reset(void);
        void Call(void);
        bool Return(void);

        const char *Get_Name(void) { return Name; }
        int Get_Total_Calls(void) { return TotalCalls; }
        float Get_Total_Time(void) { return TotalTime; }

    protected:
        const char *Name;
        int TotalCalls;
        float TotalTime;
        int64_t StartTime;
        int RecursionCounter;

        CProfileNode *Parent;
        CProfileNode *Child;
        CProfileNode *Sibling;
    };

    // An iterator to navigate through the tree
    class CProfileIterator
    {
    public:
        // Access all the children of the current parent
        void First(void);
        void Next(void);
        bool Is_Done(void);

        void Enter_Child(int index);    // Make the given child the new parent
        void Enter_Largest_Child(void); // Make the largest child the new parent
        void Enter_Parent(void);        // Make the current parent's parent the new parent

        // Access the current child
        const char *Get_Current_Name(void) { return CurrentChild->Get_Name(); }
        int Get_Current_Total_Calls(void) { return CurrentChild->Get_Total_Calls(); }
        float Get_Current_Total_Time(void) { return CurrentChild->Get_Total_Time(); }

        // Access the current parent
        const char *Get_Current_Parent_Name(void) { return CurrentParent->Get_Name(); }
        int Get_Current_Parent_Total_Calls(void) { return CurrentParent->Get_Total_Calls(); }
        float Get_Current_Parent_Total_Time(void) { return CurrentParent->Get_Total_Time(); }

    protected:
        CProfileNode *CurrentParent;
        CProfileNode *CurrentChild;

        CProfileIterator(CProfileNode *start);
        friend class CProfileManager;
    };

    typedef struct
    {
        std::string Name;
        std::string NameParent;
        std::string NameChild;
        std::string NameSibling;
        int TotalCalls;
        float TotalTime;
    } ProfileNodeInfo;

    // The Manager for the Profile system
    class CProfileManager
    {
    public:
        static void Start_Profile(const char *name);
        static void Stop_Profile(void);

        static void Reset(void);
        static void Increment_Frame_Counter(void);
        static int Get_Frame_Count_Since_Reset(void) { return FrameCounter; }
        static float Get_Time_Since_Reset(void);

        static CProfileIterator *Get_Iterator(void) { return new CProfileIterator(&Root); }
        static void Release_Iterator(CProfileIterator *iterator) { delete iterator; }

        static void DumpProfileInfo();

    private:
        static CProfileNode Root;
        static CProfileNode *CurrentNode;
        static int FrameCounter;
        static int64_t ResetTime;
        static std::vector<ProfileNodeInfo> InfoList;
    };

    // ProfileSampleClass is a simple way to profile a function's scope
    // Use the PROFILE macro at the start of scope to time
    class CProfileSample
    {
    public:
        CProfileSample(const char *name)
        {
            CProfileManager::Start_Profile(name);
        }

        ~CProfileSample(void)
        {
            CProfileManager::Stop_Profile();
        }
    };

#ifdef RK_DEBUG
#define RK_PROFILE_TICK_2(name, line) CProfileSample __profile##line(name)
#define RK_PROFILE_TICK(name)  RK_PROFILE_TICK_2(name, __LINE__)
#else
#define RK_PROFILE_TICK(name)
#endif
} // namespace Rocket
