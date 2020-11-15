cmake_minimum_required (VERSION 2.6)
project( RocketGE )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_BUILD_TYPE "Release")
IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
    ADD_DEFINITIONS(-DDEBUG)
ENDIF()

message(STATUS "###################################")
message(STATUS "operation system is ${CMAKE_SYSTEM}")
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS "current platform: Linux ")
    set(Linux 1)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "current platform: Windows")
    set(Windows 1)
elseif (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
    message(STATUS "current platform: FreeBSD")
    set(FreeBSD 1)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    message(STATUS "current platform: Apple Darwin")
    set(Apple 1)
else ()
    message(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
endif (CMAKE_SYSTEM_NAME MATCHES "Linux")
message(STATUS "###################################")

# TODO: should use vcpkg in windows to manage these packages
find_package(Threads REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/Thirdparty/entt/include
    ${PROJECT_SOURCE_DIR}/Thirdparty/glad/include
    ${PROJECT_SOURCE_DIR}/Thirdparty/stb_image
    ${PROJECT_SOURCE_DIR}/Thirdparty/imgui
    ${SPDLOG_INCLUDE_DIRS}
    ${YAML_CPP_INCLUDE_DIRS}
    ${glfw3_INCLUDE_DIRS}
)

include_directories(
    ${PROJECT_SOURCE_DIR}/GEBase/include
    ${PROJECT_SOURCE_DIR}/Sandbox/include
)

add_subdirectory( Thirdparty )
add_subdirectory( GEBase )
add_subdirectory( Sandbox )
