cmake_minimum_required (VERSION 2.8)

set(rproto_HEADERS
    #bookfactory.h
)

set(rproto_SOURCES
    bookfactory.cpp
)

add_library(rproto STATIC ${rproto_SOURCES} ${rproto_HEADERS})

#add_subdirectory(plugins/djvulibre)
#target_link_libraries(rproto rdjvu)
