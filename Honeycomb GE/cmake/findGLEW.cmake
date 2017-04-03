set(GLEW_INCLUDE_SEARCH_PATHS           # Declare paths where we think GLEW
                    					# header might be located.
                                        # UNIX:
	/usr/include
	/usr/local/include
	/opt/local/include
)

set(GLEW_LIBRARY_SEARCH_PATHS           # Declare paths where we think GLEW
                                        # library might be located.
                                        # UNIX:
    /opt/local/lib/
    /sw/lib
    /usr/lib/
    /usr/lib64/
    /usr/local/lib/
    /usr/local/lib64/
)

find_path(GLEW_INCLUDE                  # Look for the GLEW header file in
	NAMES                               # the search paths declared above.
		GL/glew.h
	PATHS
		${GLEW_INCLUDE_SEARCH_PATHS}
)

find_library(GLEW_LIBRARY               # Look for the GLEW library in the
	NAMES                               # search paths declared above.
		glew glew32 GLEW libGLEW.a
	PATHS
		${GLEW_LIBRARY_SEARCH_PATHS}
)

IF (GLEW_INCLUDE AND GLEW_LIBRARY)      # Check if both the include directory
    set(GLEW_FOUND TRUE)                # and the library have been found.
    message("[X] Located GLEW Include and GLEW Library")
ELSE (GLEW_INCLUDE AND GLEW_LIBRARY)
    set(GLEW_FOUND FALSE)
    message(FATAL_ERROR "[_] Located GLEW Include and GLEW Library")
ENDIF (GLEW_INCLUDE AND GLEW_LIBRARY)
