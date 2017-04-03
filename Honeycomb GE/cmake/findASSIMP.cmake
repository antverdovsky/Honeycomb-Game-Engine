set(ASSIMP_INCLUDE_SEARCH_PATHS         # Declare paths where we think ASSIMP
                    					# header might be located.
                                        # UNIX:
	/usr/include
	/usr/local/include
	/opt/local/include
)

set(ASSIMP_LIBRARY_SEARCH_PATHS         # Declare paths where we think ASSIMP
                                        # library might be located.
                                        # UNIX:
    /opt/local/lib/
    /sw/lib
    /usr/lib/
    /usr/lib64/
    /usr/local/lib/
    /usr/local/lib64/
)

find_path(ASSIMP_INCLUDE                # Look for the ASSIMP header files in
	NAMES                               # the search paths declared above.
		assimp/Importer.hpp 
        assimp/scene.h
        assimp/postprocess.h
	PATHS
		${ASSIMP_INCLUDE_SEARCH_PATHS}
)

find_library(ASSIMP_LIBRARY             # Look for the ASSIMP library in the
	NAMES                               # search paths declared above.
		assimp
	PATHS
		${ASSIMP_LIBRARY_SEARCH_PATHS}
)

IF (ASSIMP_INCLUDE AND ASSIMP_LIBRARY)    # Check if both the include directory
    set(ASSIMP_FOUND TRUE)                # and the library have been found.
    message("[X] Located ASSIMP Include and ASSIMP Library")
ELSE (ASSIMP_INCLUDE AND ASSIMP_LIBRARY)
    set(ASSIMP_FOUND FALSE)
    message(FATAL_ERROR "[_] Located ASSIMP Include and ASSIMP Library")
ENDIF (ASSIMP_INCLUDE AND ASSIMP_LIBRARY)
