cmake_minimum_required (VERSION 2.8)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_definitions(-DBUILDING_DLL)

find_package(g3log REQUIRED)
include_directories(${G3LOG_INCLUDE_DIRS})

find_package(JPEG REQUIRED)
#include_directories(${JPEG_INCLUDE_DIRS})
find_package(ZLIB REQUIRED)
#include_directories(${ZLIB_INCLUDE_DIRS})
find_package(LCMS2 REQUIRED)
#include_directories(${LCMS2_INCLUDE_DIRS})
find_package(OpenJpeg REQUIRED)
#include_directories(${OPENJPEG_INCLUDE_DIR})

find_package(Qt5Core REQUIRED)

set(HEADERS
    plugin.h
    point.h
    rect.h
    book.h
    iinternallayout.h
    layout.h
    imagetile.h
    renderer.h
)

set(SOURCES
    plugin.cpp
    book.cpp
    layout.cpp
    imagetile.cpp
    renderer.cpp
    ids.cpp
)

add_library(pdfiumglue SHARED
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(pdfiumglue
    ${G3LOG_LIBRARIES}
    ${FUTIL_LIBRARY}
    ${PDFIUM_LIBRARY}
    ${JPEG_LIBRARIES}
    ${ZLIB_LIBRARIES}
    ${LCMS2_LIBRARIES}
    ${OPENJPEG_LIBRARIES}
    clue_api
)

qt5_use_modules(pdfiumglue Core Gui)
include_directories(
    ${FUTIL_INCLUDE_DIR}
    ${CLUE_API_INCLUDE_DIR}
    ${PDFIUM_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


