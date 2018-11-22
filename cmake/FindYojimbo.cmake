# Look for a version of EntityX on the local machine
#
# By default, this will look in all common places. If EntityX is built or
# installed in a custom location, you're able to either modify the
# CMakeCache.txt file yourself or simply pass the path to CMake using either the
# environment variable `ENTITYX_ROOT` or the CMake define with the same name.

set(YOJIMBO_PATHS
        ${YOJIMBO_ROOT}
        $ENV{YOJIMBO_ROOT}
        /usr/local/include
        /usr/local/lib/yojimbo
        )

find_path(YOJIMBO_INCLUDE_DIR yojimbo.h PATH_SUFFIXES include PATHS ${YOJIMBO_PATHS})
find_library(YOJIMBO_LIBRARY NAMES yojimbo PATH_SUFFIXES lib PATHS ${YOJIMBO_PATHS})
find_library(YOJIMBO_LIBRARY_DEBUG NAMES yojimbo PATH_SUFFIXES lib PATHS ${YOJIMBO_PATHS})

set(YOJIMBO_LIBRARIES ${YOJIMBO_LIBRARY})
set(YOJIMBO_INCLUDE_DIRS ${YOJIMBO_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

# handle the QUIETLY and REQUIRED arguments and set YOJIMBO_FOUND to TRUE if
# all listed variables are TRUE
find_package_handle_standard_args(yojimbo DEFAULT_MSG YOJIMBO_LIBRARY YOJIMBO_INCLUDE_DIR)

mark_as_advanced(YOJIMBO_INCLUDE_DIR YOJIMBO_LIBRARY)