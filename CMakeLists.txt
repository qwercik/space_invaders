cmake_minimum_required(VERSION 3.0.0)

project(space_invaders)

add_library(lodepng
    include/lodepng/lodepng.hpp
    src/lodepng/lodepng.cpp
)
target_include_directories(lodepng PUBLIC include/)


add_executable(space_invaders
    # Main file of project
    src/space_invaders/main.cpp

    # File with some helpful functions
    include/space_invaders/utils.hpp
    src/space_invaders/utils.cpp

    # Shader loading and unloading system implementation
    include/space_invaders/shader/Shader.hpp
    include/space_invaders/shader/ShaderSet.hpp
    include/space_invaders/shader/ConstantShaderSet.hpp
    include/space_invaders/shader/LambertShaderSet.hpp
    include/space_invaders/shader/TexturedShaderSet.hpp
    include/space_invaders/shader/LambertTexturedShaderSet.hpp
    include/space_invaders/shader/CubeMapShaderSet.hpp
    include/space_invaders/shader/PhongShaderSet.hpp
    src/space_invaders/shader/Shader.cpp
    src/space_invaders/shader/ShaderSet.cpp
    src/space_invaders/shader/ConstantShaderSet.cpp
    src/space_invaders/shader/LambertShaderSet.cpp
    src/space_invaders/shader/TexturedShaderSet.cpp
    src/space_invaders/shader/LambertTexturedShaderSet.cpp
    src/space_invaders/shader/CubeMapShaderSet.cpp
    src/space_invaders/shader/PhongShaderSet.cpp

    # Models
    include/space_invaders/model/Model.hpp
    include/space_invaders/model/BasicModel.hpp
    include/space_invaders/model/ColoredModel.hpp
    include/space_invaders/model/TexturedModel.hpp
    include/space_invaders/model/HierarchicalModel.hpp
    include/space_invaders/model/predefined/Cube.hpp
    include/space_invaders/model/predefined/Teapot.hpp
    include/space_invaders/model/predefined/Wall.hpp
    src/space_invaders/model/Model.cpp
    src/space_invaders/model/BasicModel.cpp
    src/space_invaders/model/ColoredModel.cpp
    src/space_invaders/model/TexturedModel.cpp
    src/space_invaders/model/HierarchicalModel.cpp
    src/space_invaders/model/predefined/Cube.cpp
    src/space_invaders/model/predefined/Teapot.cpp
    src/space_invaders/model/predefined/Wall.cpp

    # Texture management
    include/space_invaders/texture/Texture.hpp
    include/space_invaders/texture/CubeMapTexture.hpp
    src/space_invaders/texture/Texture.cpp
    src/space_invaders/texture/CubeMapTexture.cpp

    # Window management and OpenGL initializing
    include/space_invaders/window/Window.hpp
    include/space_invaders/window/Cursor.hpp
    src/space_invaders/window/Window.cpp
    src/space_invaders/window/Cursor.cpp

    # Library for loading OBJ files
    include/obj_loader/obj_loader.h
)
target_include_directories(space_invaders PUBLIC include/)
target_compile_features(space_invaders PUBLIC cxx_std_17)

if(MSVC)
    find_package(OpenGL REQUIRED)
    add_subdirectory(glm)
    target_include_directories(space_invaders PUBLIC include_Windows_only/)
    target_link_directories(space_invaders PUBLIC lib)
    target_link_libraries(space_invaders PUBLIC
        lodepng
        glm
        glew32.lib
        glfw3.lib
        ${OPENGL_LIBRARIES}
    )
else()
    target_link_libraries(space_invaders PUBLIC -lGL -lglfw -lGLEW lodepng)
    target_compile_options(space_invaders PUBLIC -Wall -Wextra -Wpedantic -O2)
endif()

add_custom_target(run
    COMMAND ./space_invaders
    DEPENDS space_invaders
)

add_custom_target(run-mesa
    COMMAND MESA_GL_VERSION_OVERRIDE=3.4 ./space_invaders
    DEPENDS space_invaders
)
