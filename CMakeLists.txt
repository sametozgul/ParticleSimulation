cmake_minimum_required(VERSION 3.5)

project(Instancing LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES
    main.cpp
    src/glad.c
    window/*
    imgui/*
    tools/*
    opengl/*
    model/*
    shaders/*
   )
add_executable(Instancing ${SOURCES} )
target_include_directories(Instancing PUBLIC imgui include src window tools opengl model)

find_package(glfw3 3.3 REQUIRED)
# Find and include GLM
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
# Find and include GLFWa
find_package(glm REQUIRED)


file(GLOB GLSL_SOURCE_FILES
    shaders/*.frag
    shaders/*.vert
)

add_custom_target(
    Shaders
    DEPENDS ${GLSL_SOURCE_FILES}
)
add_dependencies(Instancing Shaders)

add_custom_command(TARGET Shaders POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "$<TARGET_PROPERTY:Instancing,SOURCE_DIR>/shaders"
    "$<TARGET_PROPERTY:Instancing,BINARY_DIR>/$<CONFIGURATION>/shaders"
)
target_link_libraries(Instancing  OpenGL::GL glfw glm::glm ${GLFW3_LIBRARY})

install(TARGETS Instancing
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
