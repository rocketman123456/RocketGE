message(STATUS "Add Module Sandbox")
message(STATUS "###################################")
include_directories(
    ${PROJECT_SOURCE_DIR}/Rocket/Interface
    ${PROJECT_SOURCE_DIR}/Sandbox/SandboxApp
    ${PROJECT_SOURCE_DIR}/Sandbox/Sandbox2D
)

add_subdirectory( SandboxApp )
add_subdirectory( Sandbox2D )
