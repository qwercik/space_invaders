cmake_minimum_required(VERSION 3.0.0)

project(space_invaders)

add_executable(space_invaders
    # Main file of project
    src/space_invaders/main.cpp

    # File with some helpful functions
    include/space_invaders/utils.hpp

    # Shader loading and unloading system implementation
    include/space_invaders/shader/Shader.hpp
    include/space_invaders/shader/ShaderSet.hpp
    src/space_invaders/utils.cpp
    src/space_invaders/shader/Shader.cpp
    src/space_invaders/shader/ShaderSet.cpp

    # Models
    include/space_invaders/model/Model.hpp
    include/space_invaders/model/BasicModel.hpp
    include/space_invaders/model/Cube.hpp
    include/space_invaders/model/Teapot.hpp
    src/space_invaders/model/Model.cpp
    src/space_invaders/model/BasicModel.cpp
    src/space_invaders/model/Teapot.cpp


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
