cmake_minimum_required (VERSION 2.6)
project( RocketGE )

SET(CMAKE_BUILD_TYPE "Debug")
#SET(CMAKE_BUILD_TYPE "Release")

find_package(Threads REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(glfw3 REQUIRED)

# spdlog library
#find_package(spdlog REQUIRED)
add_library(spdlog::spdlog STATIC IMPORTED)
add_library(spdlog::spdlog_header_only INTERFACE IMPORTED)

include_directories(
    ${PROJECT_SOURCE_DIR}/Thirdparty/entt/include
    ${PROJECT_SOURCE_DIR}/Thirdparty/glad/include
    ${PROJECT_SOURCE_DIR}/Thirdparty/stb_image
    ${PROJECT_SOURCE_DIR}/Thirdparty/imgui
    #${spdlog_INCLUDE_DIRS}
    ${YAML_CPP_INCLUDE_DIRS}
    ${glfw3_INCLUDE_DIRS}
)

add_subdirectory( Thirdparty )
add_subdirectory( GEBase )

