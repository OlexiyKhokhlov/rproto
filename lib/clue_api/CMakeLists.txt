cmake_minimum_required (VERSION 2.8)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(g3log REQUIRED)
include_directories(${G3LOG_INCLUDE_DIRS})

find_package(Qt5Core REQUIRED)

set(HEADERS
    include/bookfactory.h
    include/ipoint.h
    include/irect.h
    include/basepoint.h
    include/baserect.h
    include/iimagetile.h
    include/ibook.h
    include/ilayout.h
    include/iplugin.h
    include/irenderer.h
)

set(SOURCES
    ids.cpp
    bookfactory.cpp
    basepoint.cpp
    baserect.cpp
)

add_library(clue_api STATIC
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(clue_api ${G3LOG_LIBRARIES})

qt5_use_modules(clue_api Core)
include_directories(
    ${FUTIL_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


