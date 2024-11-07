# Litenet Project Journal

## 2024-11-02 (Morning Update)

This morning we focused on setting up the development environment.

Created the project and associated local and github repositories. Set up the initial project structure with `roadmap.md` and `journal.md` for planning and progress tracking.

Set up a conda environment with just the essentials: Python 3.11,  NumPy for testing and benchmarking, pytest for testing, and CMake for our C build system. We're using clang as our C compiler.

Created the basic project structure that supports both Python and C components. The Python part is set up as an installable package using setup.py, which will allow us to test the library as we build it. The C part is configured with CMake.

Created the configuration files for the C build system with CMake (tested), Python package configuration with setup.py (tested), and a .gitignore file. 

Key decisions made today:
- Keep the setup minimal but expandable
- Use Python for high-level API and C for performance-critical operations   
- Set up the project as an installable package from the start

## 2024-11-02 (Afternoon Update)

Refined project focus. We'll try to prioritize time-series forecasting capabilities first, then update the roadmap to reflect this priority shift by adding specific sections for time-series operations and forecasting models.

Decided to implement N-D Tensors from the get-go. Made a granular task list to implement the Core Tensor Data Structure and Fundamental Tensor Operations with several simplifying design decisions. 

Began implementing the Tensor data structure in C @ src/c/core/tensor/`tensor.h` and `tensor.c`.

## 2024-11-03

