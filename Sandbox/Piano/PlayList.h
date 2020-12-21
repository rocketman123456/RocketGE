#pragma once
#include "RKEngine.h"
#include "yaml-cpp/yaml.h"

class CustomTimer
{
public:
    void InitTime(void);
    float GetExactTime(void);

private:
    std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
    std::chrono::time_point<std::chrono::steady_clock> m_CurrentTimepoint;
    long long m_TimeLastTick;
};

class PlayList
{
public:
    PlayList(const std::string &path, float step = 0.25f);

    void Play(const std::string &name);

private:
    typedef std::pair<float, std::string> Note;
    typedef std::vector<Note> MusicList;
    YAML::Node m_Conf;
    std::string m_Path;
    std::map<std::string, MusicList> m_List;
    float m_Step = 0.25;
};
