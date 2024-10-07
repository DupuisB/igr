cmake_minimum_required(VERSION 3.10)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project name
project(tpOpenGL)

# Add the executable
add_executable(${PROJECT_NAME} main.cpp)

# Add GLFW as a subdirectory
add_subdirectory(glfw)

# Link GLFW library
target_link_libraries(${PROJECT_NAME} glfw)

# Include GLAD sources
target_sources(${PROJECT_NAME} PRIVATE glad/src/gl.c) # If GLAD1, glad/src/glad.c
target_include_directories(${PROJECT_NAME} PRIVATE glad/include/)

# Find and link GLM
find_package(glm REQUIRED)

# Link GLM's include directory
target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIRS})

