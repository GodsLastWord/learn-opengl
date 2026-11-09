cmake_minimum_required(VERSION 3.16)

project(
    LearnOpenGL
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EXTERNAL_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/external")

file(GLOB_RECURSE LEARN_OPENGL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(main ${LEARN_OPENGL_SOURCES})
target_include_directories(main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory("${EXTERNAL_LIBRARIES}/glfw")
add_subdirectory("${EXTERNAL_LIBRARIES}/glad")

target_link_libraries(main PRIVATE glfw glad)
