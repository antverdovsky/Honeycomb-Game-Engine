cmake_minimum_required(VERSION 3.1)     # Version 3.1 required
project(HGE_GIT)                        # Honeycomb (GitHub Repository)

                                        # Export final executable to the
                                        # the executable folder, since the
                                        # resource paths used to import assets
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY      # are relative to the exe location.
    ${CMAKE_CURRENT_SOURCE_DIR}/executable)

add_subdirectory("Honeycomb GE")        # Recurse into the Engine directory
add_subdirectory("Test Game")           # Recurse into the Test Game directory
