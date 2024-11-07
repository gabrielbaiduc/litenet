# This line specifies the minimum version of CMake required to process this file.
cmake_minimum_required(VERSION 3.15)

# Defines the project name as "litenet" and specifies C as the programming language.
project(litenet C)

# Enables the generation of a compile_commands.json file for IDEs to use for IntelliSense.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Tell CMake which Python to use (before find_package)
set(Python_ROOT_DIR "/Users/gabbai/miniforge3/envs/litenet") # Path to the Python installation, used to locate Python components.
set(Python_EXECUTABLE "${Python_ROOT_DIR}/bin/python3.11") # Path to the Python executable - the interpreter itself.
set(Python_INCLUDE_DIR "${Python_ROOT_DIR}/include/python3.11") # Path to the Python include directory, development files.

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Now find Python with our specifications
find_package(Python 3.11 EXACT REQUIRED COMPONENTS Development)

# Print Python paths for verification
message(STATUS "Python_INCLUDE_DIRS: ${Python_INCLUDE_DIRS}")
message(STATUS "Python_LIBRARIES: ${Python_LIBRARIES}")

# Create shared library for Python extension
add_library(litenet_core SHARED
    src/c/tensor/tensor.c
    src/c/python/tensormodule.c
)

# Add Python include directories
target_include_directories(litenet_core PRIVATE
    ${Python_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src/c
)

# Set library properties
set_target_properties(litenet_core PROPERTIES
    PREFIX ""
    OUTPUT_NAME "litenet"
)

# Link against Python libraries
target_link_libraries(litenet_core PRIVATE Python::Python)