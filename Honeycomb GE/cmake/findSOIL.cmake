set(SOIL_INCLUDE_SEARCH_PATHS           # Declare paths where we think SOIL
                    					# header might be located.
                                        # UNIX:
	/usr/include/SOIL
	/usr/local/include/SOIL
	/opt/local/include/SOIL
)

set(SOIL_LIBRARY_SEARCH_PATHS           # Declare paths where we think SOIL
                                        # library might be located.
                                        # UNIX:
    /opt/local/lib/
    /sw/lib
    /usr/lib/
    /usr/lib64/
    /usr/local/lib/
    /usr/local/lib64/
)

find_path(SOIL_INCLUDE                  # Look for the SOIL header file in
	NAMES                               # the search paths declared above.
		SOIL.h
	PATHS
		${SOIL_INCLUDE_SEARCH_PATHS}
)

find_library(SOIL_LIBRARY               # Look for the SOIL library in the
	NAMES                               # search paths declared above.
		SOIL libSOIL.a
	PATHS
		${SOIL_LIBRARY_SEARCH_PATHS}
)

IF (SOIL_INCLUDE AND SOIL_LIBRARY)      # Check if both the include directory
    set(SOIL_FOUND TRUE)                # and the library have been found.
    message("[X] Located SOIL Include and SOIL Library")
ELSE (SOIL_INCLUDE AND SOIL_LIBRARY)
    set(SOIL_FOUND FALSE)
    message(FATAL_ERROR "[_] Located SOIL Include and SOIL Library")
ENDIF (SOIL_INCLUDE AND SOIL_LIBRARY)
