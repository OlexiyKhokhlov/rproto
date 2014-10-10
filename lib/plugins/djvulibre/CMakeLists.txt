cmake_minimum_required (VERSION 2.6)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

find_package(DJVULibre REQUIRED)

QT4_WRAP_CPP(rdjvu_MOCS
    djvulistener.h
    djvubook.h
    djvurenderer.h
    djvupagelayout.h
)

add_library(rdjvu SHARED
  djvuplugin.h
  djvuplugin.cpp
  djvubook.cpp
  djvubook.h
  djvupagelayout.cpp 
  djvupagelayout.h
  djvurenderer.cpp
  djvurenderer.h
  djvulistener.h
  djvulistener.cpp
  ${rdjvu_MOCS}
)




target_link_libraries(rdjvu ${DJVULIBRE_LIBRARIES})
include_directories(
    ${RPROTO_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${DJVULIBRE_INCLUDE_DIR}
)
