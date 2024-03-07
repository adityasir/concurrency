cmake_minimum_required(VERSION 3.12)
project(CombinedProjects)

# Add the lock_based directory
add_subdirectory(lock_based)

# Set the available projects
set(PROJECT_OPTIONS "lock_based" "lock_free")

# Check if a valid project name is provided as a command line argument
if(NOT DEFINED PROJECT_NAME OR NOT PROJECT_NAME IN_LIST PROJECT_OPTIONS)
    message(FATAL_ERROR "Please provide a valid project name as a command line argument. Options: ${PROJECT_OPTIONS}")
endif()

# Build the specified project
build_project(${PROJECT_NAME})

