# Litenet Project Journal

## 2024-11-02

**NOTE TO SELF:** """The tone of this summary, along with the language and the depth of explanation detail is very sensible. Use this as a template for future summaries."""

Today focused on setting up the development environment.
Created the project and associated local and github repositories. Set up the initial project structure with `roadmap.md` and `journal.md` for planning and progress tracking.

Started with an ambitious plan including various development tools (linters, formatters, documentation generators), but decided to take a more minimalistic approach. The reasoning is simple: add complexity only when needed. This should help us focus on the core functionality first.

Set up a conda environment with just the essentials: Python 3.11 (initially tried 3.13 but stepped back for better compatibility), NumPy for testing and benchmarking, pytest for testing, and CMake for our C build system. On the C side, we're using the system's clang compiler (via Xcode Command Line Tools) instead of gcc, as it's the natural choice for macOS.

Created the basic project structure that supports both Python and C components. The Python part is set up as an installable package using setup.py, which will allow us to test the library as we build it. The C part is configured with CMake, providing a foundation for our performance-critical tensor operations. Tested the setup with a simple "Hello World" C program to verify the build system works correctly.

Created a .gitignore file to keep the repository clean of build artifacts and system-specific files. Decided to postpone creating a README.md and publishing to PyPI until we have some useful functionality implemented.

Key decisions made today:
- Keep the setup minimal but expandable
- Use Python for high-level API and C for performance-critical operations   
- Set up the project as an installable package from the start
- Organize code in a way that separates Python and C components clearly

Next steps will focus on implementing the basic tensor structure in C, following the roadmap we created yesterday.

## 2024-11-02 (Afternoon Update)

Refined project focus. We're prioritizing time-series forecasting capabilities first.

Updated the roadmap to reflect this priority shift. Added specific sections for time-series operations and forecasting models.Restructured initial focus areas to emphasize time-series functionality

Next steps remain the same - implementing basic tensor structure, but with additional consideration for time-series specific requirements.