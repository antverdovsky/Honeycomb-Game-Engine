cmake_minimum_required(VERSION 3.1)     # Version 3.1 required

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -g")

file(GLOB_RECURSE SOURCES               # Fetch all of the Engine's Srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(                            # Create the Engine Library from Srcs
    HoneycombGameEngine ${SOURCES}
)

find_package(OpenGL REQUIRED)           # Find OpenGL

include(                                # Find the SOIL Library
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/findSOIL.cmake
)

include(                                # Find the GLEW Library
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/findGLEW.cmake
)

include(                                # Find the GLFW3 Library
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/findGLFW.cmake
)

include(                                # Find the ASSIMP Library
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/findASSIMP.cmake
)

target_include_directories(             
    HoneycombGameEngine
    PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}         # Add all of the Headers to the Engine
    
    ${OPENGL_INCLUDE_DIRS}              # and all of the external dependencies
    ${SOIL_INCLUDE}
    ${GLEW_INCLUDE}
    ${GLFW_INCLUDE}    
    ${ASSIMP_INCLUDE}
)

target_link_libraries(                  # Link the libraries to the Engine
    HoneycombGameEngine

    ${OPENGL_LIBRARIES}
    ${SOIL_LIBRARY}
    ${GLEW_LIBRARY}
    ${GLFW_LIBRARY}
    ${ASSIMP_LIBRARY}
)
