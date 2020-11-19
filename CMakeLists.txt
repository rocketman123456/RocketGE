cmake_minimum_required (VERSION 2.6)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(VCPKG_ROOT "/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE PATH "")
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(VCPKG_ROOT "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE PATH "")
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(VCPKG_ROOT "/usr/local/Cellar/vcpkg/2020.11-1/libexec/scripts/buildsystems/vcpkg.cmake" CACHE PATH "")
endif ()
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT})

message(STATUS "###################################")

message(STATUS "CMAKE_TOOLCHAIN_FILE ${CMAKE_TOOLCHAIN_FILE}")
project( RocketGE )
message(STATUS "Project Name ${PROJECT_NAME}")

message(STATUS "###################################")

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Debug")
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
    add_definitions(-DPLATFORM_LINUX)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "current platform: Windows")
    set(Windows 1)
    add_definitions(-DPLATFORM_WINDOWS)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    message(STATUS "current platform: Apple Darwin")
    set(Apple 1)
    add_definitions(-DPLATFORM_APPLE)
else ()
    message(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
endif ()

message(STATUS "###################################")

find_package(Threads REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

message(STATUS "###################################")

message(STATUS "Render API Set to OpenGL")
set(OpenGL 1)
add_definitions(-DRK_OPENGL)

message(STATUS "###################################")

include_directories(
    ${PROJECT_SOURCE_DIR}/Thirdparty/entt/include
    ${PROJECT_SOURCE_DIR}/Thirdparty/glad/include
    ${PROJECT_SOURCE_DIR}/Thirdparty/spdlog/include
    ${PROJECT_SOURCE_DIR}/Thirdparty/stb_image
    ${PROJECT_SOURCE_DIR}/Thirdparty/imgui
)

include_directories(
    ${PROJECT_SOURCE_DIR}/RocketGE/include
    ${PROJECT_SOURCE_DIR}/GEEngine/include
    ${PROJECT_SOURCE_DIR}/Sandbox/include
)

if(OpenGL)
    include_directories(${PROJECT_SOURCE_DIR}/GERender/OpenGL/include)
elseif(Vulkan)
    include_directories(${PROJECT_SOURCE_DIR}/GERender/Vulkan/include)
elseif(Metal)
    include_directories(${PROJECT_SOURCE_DIR}/GERender/Metal/include)
endif()

if(Apple)
    include_directories( ${PROJECT_SOURCE_DIR}/Platform/Apple/include )
elseif(Linux)
    include_directories( ${PROJECT_SOURCE_DIR}/Platform/Linux/include )
elseif(Windows)
    include_directories( ${PROJECT_SOURCE_DIR}/Platform/Windows/include )
endif()

add_subdirectory( Thirdparty )
add_subdirectory( Platform )

add_subdirectory( GEEngine )
add_subdirectory( GERender )
add_subdirectory( RocketGE )

add_subdirectory( Sandbox )
