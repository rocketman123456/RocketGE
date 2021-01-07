message(STATUS "Add Module RayTrace")
message(STATUS "###################################")

if(Apple)
add_executable( OpenAL01
    OpenAL01.cpp
)
target_link_libraries( OpenAL01 PRIVATE 
    OpenAL::OpenAL SndFile::sndfile
)
endif()