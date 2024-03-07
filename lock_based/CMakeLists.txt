cmake_minimum_required(VERSION 3.12)
project(lock_based)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Source files for the lock_based component
set(SOURCE_FILES lock_based.cpp lock_based.h)

# Add an executable target
add_executable(lock_based ${SOURCE_FILES})

# Link pthread library
target_link_libraries(lock_based PRIVATE pthread)

