set(OPEN_GL_LIBRARY_SEARCH_PATHS        # Declare paths where we think OpenGL
                                        # library might be located.
                                        # UNIX:
    /opt/local/lib/
    /sw/lib
    /usr/lib/
    /usr/lib64/
    /usr/local/lib/
    /usr/local/lib64/
)

find_library(OPEN_GL_LIBRARY            # Look for the OpenGL library in the
	NAMES                               # search paths declared above.
		opengl
	PATHS
		${OPEN_GL_LIBRARY_SEARCH_PATHS}
)

IF (OPEN_GL_LIBRARY)                    # Check if the library has been found.
    set(OPEN_GL_FOUND TRUE)                
    message("[X] Located OpenGL Library")
ELSE (OPEN_GL_LIBRARY)
    set(OPEN_GL_FOUND FALSE)
    message(FATAL_ERROR "[_] Located OpenGL Library")
ENDIF (OPEN_GL_LIBRARY)
