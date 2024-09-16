# Minimum CMake version required
cmake_minimum_required(VERSION 3.30)

# Project name and version
project(SimpleOpenGL)

# Set the C++ standard to C++11 (or newer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(THREADS_PREFER_PTHREAD_FLAG ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --target=x86_64-w64-mingw32")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --target=x86_64-w64-mingw32")

# Add the executable (the source file is main.cpp)
add_executable(gladTest src/main.cpp src/glapp.cpp src/glad.c src/shader.cpp)
target_include_directories(gladTest PRIVATE ${PROJECT_SOURCE_DIR}/include)

# find_package(Threads REQUIRED)
# target_link_libraries(gladTest Threads::Threads)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.4 REQUIRED)
find_package(glm REQUIRED)
target_link_libraries(gladTest glfw glm::glm)
target_link_libraries(gladTest OpenGL::GL)
