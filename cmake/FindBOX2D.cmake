# Locate Box2D
# This module defines XXX_FOUND, XXX_INCLUDE_DIRS and XXX_LIBRARIES standard variables

FIND_PATH(BOX2D_INCLUDE_DIR Box2D.h
        HINTS
        $ENV{BOX2D_DIR}
        $ENV{BOX2D_PATH}
        ${ADDITIONAL_SEARCH_PATHS}
        PATH_SUFFIXES include Include include/Box2D
        PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw # Fink
        /opt/local # DarwinPorts
        /opt/csw # Blastwave
        /opt
        )

FIND_LIBRARY(BOX2D_RELEASE_LIBRARY
        NAMES box2d Box2d BOX2D Box2D
        HINTS
        $ENV{BOX2D_DIR}
        $ENV{BOX2D_PATH}
        ${ADDITIONAL_SEARCH_PATHS}
        PATH_SUFFIXES lib64 lib lib/release Library
        PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw
        /opt/local
        /opt/csw
        /opt
        )

FIND_LIBRARY(BOX2D_LIBRARY_DEBUG
        NAMES box2dd box2d_d
        HINTS
        $ENV{BOX2D_DIR}
        $ENV{BOX2D_PATH}
        ${ADDITIONAL_SEARCH_PATHS}
        PATH_SUFFIXES lib64 lib lib/debug Library
        PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw
        /opt/local
        /opt/csw
        /opt
        )


IF (BOX2D_RELEASE_LIBRARY)
    IF (BOX2D_DEBUG_LIBRARY)
        SET(BOX2D_LIBRARY optimized "${BOX2D_RELEASE_LIBRARY}" debug "${BOX2D_DEBUG_LIBRARY}")
    ELSE ()
        SET(BOX2D_LIBRARY "${BOX2D_RELEASE_LIBRARY}")        # Could add "general" keyword, but it is optional
    ENDIF ()
ENDIF ()

MARK_AS_ADVANCED(BOX2D_LIBRARY BOX2D_RELEASE_LIBRARY BOX2D_DEBUG_LIBRARY BOX2D_INCLUDE_DIR)

# Per-recommendation
SET(BOX2D_INCLUDE_DIRS "${BOX2D_INCLUDE_DIR}")
SET(BOX2D_LIBRARIES "${BOX2D_LIBRARY}")

# handle the QUIETLY and REQUIRED arguments and set BOX2D_FOUND to TRUE if
# all listed variables are TRUE

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Box2D DEFAULT_MSG BOX2D_LIBRARY BOX2D_INCLUDE_DIR)