cmake_minimum_required(VERSION 3.0.0)

project(space_invaders)

add_executable(space_invaders
    src/space_invaders/main.cpp

    include/space_invaders/utils.hpp
    include/space_invaders/shader/Shader.hpp
    include/space_invaders/shader/ShaderSet.hpp
    src/space_invaders/utils.cpp
    src/space_invaders/shader/Shader.cpp
    src/space_invaders/shader/ShaderSet.cpp
)
target_include_directories(space_invaders PUBLIC include/)
target_link_libraries(space_invaders PUBLIC -lGL -lglfw -lGLEW)
target_compile_features(space_invaders PUBLIC cxx_std_17)
target_compile_options(space_invaders PUBLIC -Wall -Wextra -Wpedantic -O2)


add_custom_target(run
    COMMAND ./space_invaders
    DEPENDS space_invaders
)

add_custom_target(run-mesa
    COMMAND MESA_GL_VERSION_OVERRIDE=3.4 ./space_invaders
    DEPENDS space_invaders
)
