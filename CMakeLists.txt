# Set the minimum required version of CMake to use this file
cmake_minimum_required(VERSION 3.10)

# Define the name of the project
project(CppSocketProject)

# Use C++17 standard for all targets
set(CMAKE_CXX_STANDARD 17)

# Add the subdirectory containing the common static library (lib/common)
# This will look for lib/common/CMakeLists.txt and build the "common" library
# Includes the subdirectory's targets and configurations into the current build tree so it always 
# look for CMakeLists.txt inside the folder
add_subdirectory(lib/common)

# Add directories to the list of paths that the compiler uses to look for header files
# 'lib/common' for internal headers and 'include' for shared project headers
include_directories(
    lib/common
    include
)

# --------------------------------------------
# CLIENT CONFIGURATION

# Manually gather all .cpp files in src/client/
# like server also files can automatically added using GLOB. Manual way like this is more common.
set(CLIENT_SOURCES
    src/client/client_utils.cpp
    src/client/client.cpp
)

# Define an executable target named 'client' using the source files
add_executable(client ${CLIENT_SOURCES})

# Link the 'common' static library to the 'client' executable
target_link_libraries(client common)

# --------------------------------------------
# SERVER CONFIGURATION

# Automatically gather all .cpp files in src/server/
# GLOB command match the pattern and store the result in SERVER_SOURCES variable.
# Like client, manually also files can be added.
file(GLOB SERVER_SOURCES src/server/*.cpp)

# Define an executable target named 'server' using the source files
add_executable(server ${SERVER_SOURCES})

# Link the 'common' static library to the 'server' executable
target_link_libraries(server common)
