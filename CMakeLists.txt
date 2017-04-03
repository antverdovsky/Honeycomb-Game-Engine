cmake_minimum_required(VERSION 2.8)     # Version 3.1 required
project(HGE_GIT)                        # Honeycomb (GitHub Repository)

add_subdirectory("Honeycomb GE")        # Recurse into the Engine directory
add_subdirectory("Test Game")           # Recurse into the Test Game directory
