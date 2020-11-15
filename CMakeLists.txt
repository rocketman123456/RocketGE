cmake_minimum_required (VERSION 2.6)
project( RocketGE )

find_package(Threads REQUIRED)
#find_package(spdlog REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(glfw3 REQUIRED)

# Create imported target spdlog::spdlog
add_library(spdlog::spdlog STATIC IMPORTED)
set_target_properties(spdlog::spdlog PROPERTIES
    INTERFACE_COMPILE_DEFINITIONS "SPDLOG_COMPILED_LIB"
    INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
    INTERFACE_LINK_LIBRARIES "Threads::Threads"
)

# Create imported target spdlog::spdlog_header_only
add_library(spdlog::spdlog_header_only INTERFACE IMPORTED)
set_target_properties(spdlog::spdlog_header_only PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
    INTERFACE_LINK_LIBRARIES "Threads::Threads"
)

include_directories(
    ${PROJECT_SOURCE_DIR}/Thirdparty/entt/include
    ${PROJECT_SOURCE_DIR}/Thirdparty/glad/include
    ${PROJECT_SOURCE_DIR}/Thirdparty/stb_image
    ${PROJECT_SOURCE_DIR}/Thirdparty/imgui
    #${spdlog_INCLUDE_DIRS}
    ${YAML_CPP_INCLUDE_DIRS}
    ${glfw3_INCLUDE_DIRS}
)


