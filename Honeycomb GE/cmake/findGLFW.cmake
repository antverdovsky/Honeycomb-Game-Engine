set(GLFW_INCLUDE_SEARCH_PATHS           # Declare paths where we think GLFW
                    					# header might be located.
                                        # UNIX:
	/usr/include
	/usr/local/include
	/opt/local/include
)

set(GLFW_LIBRARY_SEARCH_PATHS           # Declare paths where we think GLFW
                                        # library might be located.
                                        # UNIX:
    /opt/local/lib/
    /sw/lib
    /usr/lib/
    /usr/lib64/
    /usr/local/lib/
    /usr/local/lib64/
)

find_path(GLFW_INCLUDE                  # Look for the GLFW header file in
	NAMES                               # the search paths declared above.
		GLFW/glfw3.h
	PATHS
		${GLFW_INCLUDE_SEARCH_PATHS}
)

find_library(GLFW_LIBRARY               # Look for the GLFW library in the
	NAMES                               # search paths declared above.
		glfw glfw3 
	PATHS
		${GLFW_LIBRARY_SEARCH_PATHS}
)

IF (GLFW_INCLUDE AND GLFW_LIBRARY)      # Check if both the include directory
    set(GLFW_FOUND TRUE)                # and the library have been found.
    message("[X] Located GLFW Include and GLFW Library")
ELSE (GLFW_INCLUDE AND GLFW_LIBRARY)
    set(GLFW_FOUND FALSE)
    message(FATAL_ERROR "[_] Located GLFW Include and GLFW Library")
ENDIF (GLFW_INCLUDE AND GLFW_LIBRARY)
