cmake_minimum_required (VERSION 2.8)

set(CMAKE_AUTOMOC ON)

add_subdirectory(pdfium)

set(PDFIUM_INCLUDE_DIR "${DEBUG_INSTALL_ROOT}/include/pdfium")
set(PDFIUM_LIBRARY "${DEBUG_INSTALL_ROOT}/lib/libpdfium.a")

add_definitions(-DBUILDING_DLL)

#find_package(g3log REQUIRED)
#include_directories(${G3LOG_INCLUDE_DIRS})

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(JPEG REQUIRED)
#include_directories(${JPEG_INCLUDE_DIRS})
find_package(ZLIB REQUIRED)
#include_directories(${ZLIB_INCLUDE_DIRS})
find_package(LCMS2 REQUIRED)
#include_directories(${LCMS2_INCLUDE_DIRS})
find_package(OpenJpeg REQUIRED)
#include_directories(${OPENJPEG_INCLUDE_DIR})

set(HEADERS
    src/library.h
    src/plugin.h
    src/book.h
    src/point.h
    src/rect.h
    src/iinternallayout.h
    src/layout.h
    src/imagetile.h
    src/renderer.h
)

set(SOURCES
    src/library.cpp
    src/plugin.cpp
    src/book.cpp
    src/layout.cpp
    src/imagetile.cpp
    src/renderer.cpp
#    src/ids.cpp
)

add_library(pdfiumglue SHARED
    ${HEADERS}
    ${SOURCES}
)

add_dependencies(pdfiumglue pdfium)

target_link_libraries(pdfiumglue
#    ${G3LOG_LIBRARIES}
    ${FUTIL_LIBRARY}
    ${PDFIUM_LIBRARY}
    ${JPEG_LIBRARIES}
    ${ZLIB_LIBRARIES}
    ${LCMS2_LIBRARIES}
    ${OPENJPEG_LIBRARIES}
    glue_api
)

include_directories(
    ${FUTIL_INCLUDE_DIR}
    ${BOSS_INCLUDE_DIR}
    ${CLUE_API_INCLUDE_DIR}
    ${PDFIUM_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

