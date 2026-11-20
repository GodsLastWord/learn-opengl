cmake_minimum_required(VERSION 3.16)

project(
    LearnOpenGL
    LANGUAGES CXX
)

set(EXTERNAL_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(EXECUTABLE_NAME "main")

# libraries
add_subdirectory("${EXTERNAL_LIBRARIES}/glfw")
add_subdirectory("${EXTERNAL_LIBRARIES}/glad")
add_subdirectory("${EXTERNAL_LIBRARIES}/stb_image")
add_subdirectory("${EXTERNAL_LIBRARIES}/glm")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE LEARN_OPENGL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${EXECUTABLE_NAME} ${LEARN_OPENGL_SOURCES})
target_include_directories(${EXECUTABLE_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(${EXECUTABLE_NAME} PRIVATE glfw glad stb_image glm)
