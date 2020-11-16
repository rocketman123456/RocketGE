message(STATUS "Add Module GEWindow")
message(STATUS "###################################")
add_library(GEWindow
    src/Window.cpp
)
if(Apple)
    target_link_libraries(GEWindow Platform_Apple)
elseif(Linux)
    target_link_libraries(GEWindow Platform_Linux)
elseif(Windows)
    target_link_libraries(GEWindow Platform_Windows)
endif()
