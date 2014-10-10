# - Try to find DjVuLibre
# Once done this will define
#
# DJVULIBRE_FOUND - system has DjVuLibre
# DJVULIBRE_INCLUDE_DIRS - the include directories for DjVuLibre headers
# DJVULIBRE_LIBRARIES - link these to use DjVuLibre

if (DJVULIBRE_LIBRARIES)
   # in cache already
   SET(DJVULIBRE_FIND_QUIETLY TRUE)
endif (DJVULIBRE_LIBRARIES)

find_package(PkgConfig)

if (PKG_CONFIG_FOUND)
endif (PKG_CONFIG_FOUND)

pkg_check_modules(DJVULIBRE_PKG ddjvuapi)

# Paths

find_path(DJVULIBRE_INCLUDE_DIR
    NAMES ddjvuapi.h
    HINTS ${DJVULIBRE_PKG_INCLUDE_DIRS}
    PATHS /usr/include /usr/local/include
    PATH_SUFFIXES libdjvu
)
if (NOT DJVULIBRE_INCLUDE_DIR)
    message(STATUS "Could not find djvulibre include dir")
    set(DJVULIBRE_FOUND FALSE)
endif (NOT DJVULIBRE_INCLUDE_DIR)

# Libraries

find_library(DJVULIBRE_LIBRARY
    NAMES djvulibre libdjvulibre
    HINTS ${DJVULIBRE_PKG_LIBRARY_DIRS}
    PATHS /usr/lib /usr/local/lib
)
if (NOT DJVULIBRE_LIBRARY)
    message(STATUS "Could not find libdjvulibre")
    set(DJVULIBRE_FOUND FALSE)
endif (NOT DJVULIBRE_LIBRARY)


set(DJVULIBRE_INCLUDE_DIRS ${DJVULIBRE_INCLUDE_DIR})
set(DJVULIBRE_LIBRARIES ${DJVULIBRE_LIBRARY})

if (DJVULIBRE_INCLUDE_DIRS AND DJVULIBRE_LIBRARIES)
    set(DJVULIBRE_FOUND TRUE)
else (DJVULIBRE_INCLUDE_DIRS AND DJVULIBRE_LIBRARIES)
    set(DJVULIBRE_FOUND FALSE)
endif (DJVULIBRE_INCLUDE_DIRS AND DJVULIBRE_LIBRARIES)