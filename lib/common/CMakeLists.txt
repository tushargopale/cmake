# Does lib/common/CMakeLists.txt need cmake_minimum_required() or project()?
# 🚫 No, it doesn’t — and shouldn’t.
# When using add_subdirectory(lib/common) from the top-level CMakeLists.txt, the lib/common/CMakeLists.txt file:
# Inherits the CMake version and project settings from the root.
# Should not redefine project() or cmake_minimum_required() — doing so can confuse the build system, especially with multiple targets.
####################################################

# This file defines the static library 'common'

# Collect all .cpp source files in this directory
file(GLOB COMMON_SOURCES
    *.cpp
)

# Create a static library named 'common' from the source files at path lib/common
add_library(common STATIC ${COMMON_SOURCES})

# Include the current directory so headers like "common.hpp" and "utils.hpp" can be found
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# (Optional) Set compile options for this library (e.g., warnings)
# target_compile_options(common PRIVATE -Wall -Wextra -pedantic)
