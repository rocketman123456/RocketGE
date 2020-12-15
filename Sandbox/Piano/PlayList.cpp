#include "PlayList.h"

void CustomTimer::InitTime()
{
    m_StartTimepoint = std::chrono::high_resolution_clock::now();
    m_CurrentTimepoint = std::chrono::high_resolution_clock::now();
    m_TimeLastTick = 10;
}

float CustomTimer::GetExactTime(void)
{
    m_CurrentTimepoint = std::chrono::high_resolution_clock::now();
    long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
    long long end = std::chrono::time_point_cast<std::chrono::microseconds>(m_CurrentTimepoint).time_since_epoch().count();

    float duration = (end - start) * 0.001f * 0.001f;
    return duration;
}

PlayList::PlayList(const std::string& path, float step)
    : m_Path(path), m_Step(step)
{
    m_Conf = YAML::LoadFile(m_Path);

    std::string prefix = "Piano.ff.";

    for(YAML::const_iterator name_it=m_Conf.begin();name_it != m_Conf.end();++name_it) {
        MusicList play_list;
        YAML::Node music = m_Conf[name_it->first.as<std::string>()];
        for(YAML::const_iterator it=music.begin();it != music.end();++it) {
            Note key(it->first.as<float>(), prefix + it->second.as<std::string>());       // <- key
            play_list.push_back(key);
        }
        m_List[name_it->first.as<std::string>()] = play_list;
    }
}

void PlayList::Play(const std::string& name)
{
    RK_TRACE("Start {0}", name);
    int index = 0;
    auto play_list = m_List[name];
    auto play_size = m_List[name].size();
    CustomTimer timer;
    timer.InitTime();
    while(index <= play_size)
    {
        while(timer.GetExactTime() > play_list[index].first * m_Step)
        {
            auto key = play_list[index].second;
            Rocket::AudioEvent event(key);
            Rocket::Application::Get().OnEvent(event);
            ++index;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    RK_TRACE("End {0}", name);
}