# CMake orchestrates the build process. In simple terms, the build process is compiling and linking our own code and external dependencies. 
# This file is the configuration file for CMake. It tells CMake what to do. It does't actually compile or link, it just configures - creates a recipe or build system/build file.
# Final compilation is done via the CLI.
cmake_minimum_required(VERSION 3.15)
project(litenet C)

# Enables the generation of a compile_commands.json file for IDEs to use for IntelliSense.
# This is important. C is not aware of Python environments. This means that we have to configure CMake to know where to find the correct Python installation which we do below. 
# This line, ensures that the configuration that we do below is exported to the compile_commands.json file which is then used by Cursor to provide IntelliSense, warnings, autocompletion, etc.
# Without this, we'd have to manually configure Cursor to use the same Python as CMake. This synces CMake and Cursor.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Tell CMake which Python to use (before find_package). As mentioned above, C is not aware of Python environments. With these lines, we ensure that CMake uses the Python that we want.
set(Python_ROOT_DIR "/Users/gabbai/miniforge3/envs/litenet") # Path to the Python installation, used to locate Python components.
set(Python_EXECUTABLE "${Python_ROOT_DIR}/bin/python3.11") # Path to the Python executable - the interpreter itself.
set(Python_INCLUDE_DIR "${Python_ROOT_DIR}/include/python3.11") # Path to the Python include directory, development files.

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Now find Python with our specifications, these include header files and libraries like `Python.h`. 
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