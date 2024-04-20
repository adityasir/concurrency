cmake_minimum_required(VERSION 3.0)
project(activeobject)

# Compile flags (adjust based on your needs)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")  # Enable warnings and debugging symbols

# Source files
set(SOURCE_FILES
    main.cpp
    #src/event_thread.cpp
    #src/interrupt_handler.cpp
    # Add other source files here
)

# Header files
set(HEADER_FILES
    inc/CThread.hpp
    inc/CThreadException.hpp
    inc/CThreadControl.hpp
    #include/event.h
    # Add other header files here
)

# Include directories (adjust as needed)
include_directories(include)

# Create the executable
add_executable(activeobject ${SOURCE_FILES})

# Link with necessary libraries (add any required libraries here)
target_link_libraries(activeobject pthread)

