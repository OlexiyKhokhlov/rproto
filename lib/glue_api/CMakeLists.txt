cmake_minimum_required (VERSION 3.2)

#set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

#find_package(g3log REQUIRED)
#include_directories(${G3LOG_INCLUDE_DIRS})

set(HEADERS
    include/forward.h
    include/ipoint.h
    include/irect.h
    include/basepoint.h
    include/baserect.h
    include/iimagetile.h
    include/ibook.h
    include/ilayout.h
    include/iplugin.h
    include/irenderer.h
    include/icontent.h
)

set(SOURCES
    basepoint.cpp
    baserect.cpp
)

add_library(glue_api STATIC
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(glue_api
    #${G3LOG_LIBRARIES}
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


