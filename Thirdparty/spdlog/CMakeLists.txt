add_library(spdlog
    src/fmt.cpp 
    src/spdlog.cpp 
    src/stdout_sinks.cpp 
    src/color_sinks.cpp 
    src/file_sinks.cpp 
    src/async.cpp 
    src/cfg.cpp
)
target_compile_definitions(spdlog PUBLIC SPDLOG_COMPILED_LIB)
