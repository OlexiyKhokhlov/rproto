cmake_minimum_required (VERSION 3.2)

find_package(DJVULibre REQUIRED)

add_library(djvuglue SHARED
#  module.cpp
  djvuplugin.h
  djvuplugin.cpp
  djvubook.cpp
  djvubook.h
  djvupagelayout.cpp
  djvupagelayout.h
  djvurenderer.cpp
  djvurenderer.h

)

target_link_libraries(djvuglue
#    ${G3LOG_LIBRARIES}
    ${DJVULIBRE_LIBRARIES}
    glue_api
)

include_directories(
    ${FUTIL_INCLUDE_DIR}
    ${CLUE_API_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${DJVULIBRE_INCLUDE_DIR}
)
