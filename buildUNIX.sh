mkdir -p "executable"                   # Create folder which stores exe
mkdir -p "build"                        # Create build dir
cd build                                # Go to the build dir
cmake ../                               # CMake the project
make                                    # Build the project
