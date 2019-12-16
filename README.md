# Neighborhood-Based Clustering using k-NN and k+-NN with Triangle Inequality

Project is organized as MS VS2017 solution.

NBC algorithm is implemented and built to DLL and CPython module (PYD + .py files), providing C++ and Python interfaces.
Furthermore, console interface is provided

## Setup

run setup\setup.py script to:

- Download libraries and tools. Full list is given in downlaod_libraries.py script
- Confiure python module build

If libraries are already in libs directory, they will not be downloaded. This is determined by checking if their subdirectories exist.

## Python module building

Python module is built with pynbc project for python version that was used to run setup script. This may result in failure of detection of library files - e.g. Win32 configuration will fail if 64-bit python is configured.
Some files from pynbc project are auto-generated during build, notably pynbc.py and pynbc.cxx. We advise to avoid panic if those files are missing from freshly-downloaded repository.
