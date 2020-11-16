cmake_minimum_required (VERSION 2.6)

set(VCPKG_ROOT "/usr/local/Cellar/vcpkg/2020.11-1/libexec/scripts/buildsystems/vcpkg.cmake" CACHE PATH "")
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT})

project( RocketGE )

message(STATUS "###################################")

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_BUILD_TYPE "Release")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DRELEASE)
endif()
message(STATUS "Build System Set to ${CMAKE_BUILD_TYPE}")

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

find_package(Threads REQUIRED)
if(Threads_FOUND)
    message(STATUS "Threads FOUND")
endif()
find_package(yaml-cpp REQUIRED)
if(yaml-cpp_FOUND)
    message(STATUS "yaml-cpp FOUND")
endif()
find_package(glfw3 REQUIRED)
if(glfw3_FOUND)
    message(STATUS "glfw3 FOUND")
endif()
find_package(spdlog REQUIRED)
if(spdlog_FOUND)
    message(STATUS "spdlog FOUND")
endif()

message(STATUS "###################################")

include_directories(
    ${PROJECT_SOURCE_DIR}/Thirdparty/entt/include
    ${PROJECT_SOURCE_DIR}/Thirdparty/glad/include
    ${PROJECT_SOURCE_DIR}/Thirdparty/stb_image
    ${PROJECT_SOURCE_DIR}/Thirdparty/imgui
    ${SPDLOG_INCLUDE_DIRS}
    ${YAML_CPP_INCLUDE_DIRS}
    ${GLFW3_INCLUDE_DIRS}
)

include_directories(
    ${PROJECT_SOURCE_DIR}/GEBase/include
    ${PROJECT_SOURCE_DIR}/GEEvent/include
    ${PROJECT_SOURCE_DIR}/Sandbox/include
)

add_subdirectory( Thirdparty )
add_subdirectory( GEBase )
add_subdirectory( Sandbox )
