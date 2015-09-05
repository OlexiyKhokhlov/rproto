cmake_minimum_required (VERSION 2.8)

add_subdirectory(pdfium)

set(PDFIUM_INCLUDE_DIR "${DEBUG_INSTALL_ROOT}/include/pdfium")
set(PDFIUM_LIBRARY "${DEBUG_INSTALL_ROOT}/lib/libpdfium.a")

add_definitions(-DBUILDING_DLL)

#find_package(g3log REQUIRED)
#include_directories(${G3LOG_INCLUDE_DIRS})

#3dparty libraries
set(USE_SYSTEM_FREETYPE ON CACHE BOOL "use system freetype")
set(USE_SYSTEM_JPEG ON CACHE BOOL "use system libjpeg")
set(USE_SYSTEM_ZLIB ON CACHE BOOL "use system zlib")
set(USE_SYSTEM_LCMS2 ON CACHE BOOL "use system lcms2")
if(WIN32)
  set(USE_SYSTEM_OPENJPEG OFF CACHE BOOL "use system openjpeg" )
else(WIN32)
  set(USE_SYSTEM_OPENJPEG ON CACHE BOOL "use system openjpeg" )
  set(USE_BINUTILS_WORKAROUND ON CACHE BOOL "use gcc-ar and gcc-ranlib instead ar and ranlib (is needed for LTO)")
endif(WIN32)

#hieroglyphs support
set(USE_GB1_MAPS OFF CACHE BOOL "use GB1 maps")
set(USE_CNS1_MAPS OFF CACHE BOOL "use CNS1 maps")
set(USE_JAPAN1_MAPS OFF CACHE BOOL "use JAPAN1 maps")
set(USE_KOREA_MAPS OFF CACHE BOOL "use KOREA maps")

find_package(Freetype)
find_package(JPEG)
find_package(ZLIB)
find_package(LCMS2)
find_package(OpenJpeg)

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
    src/content.h
)

set(SOURCES
    src/library.cpp
    src/plugin.cpp
    src/book.cpp
    src/layout.cpp
    src/imagetile.cpp
    src/renderer.cpp
    src/module.cpp
    src/content.cpp
)

add_library(pdfiumglue SHARED
    ${HEADERS}
    ${SOURCES}
)

add_dependencies(pdfiumglue pdfium)

target_link_libraries(pdfiumglue
#    ${G3LOG_LIBRARIES}
    ${PDFIUM_LIBRARY}
    ${FREETYPE_LIBRARIES}
    ${JPEG_LIBRARIES}
    ${ZLIB_LIBRARIES}
    ${LCMS2_LIBRARIES}
    ${OPENJPEG_LIBRARIES}
    glue_api
)

include_directories(
    ${UTF8_INCLUDE_DIR}
    ${FUTIL_INCLUDE_DIR}
    ${BOSS_INCLUDE_DIR}
    ${CLUE_API_INCLUDE_DIR}
    ${PDFIUM_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

