CMAKE_MINIMUM_REQUIRED (VERSION 3.2)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#find_package(g3log REQUIRED)
#include_directories(${G3LOG_INCLUDE_DIRS})

find_package(Qt5 REQUIRED Core Gui Widgets)
qt5_add_resources(reader_RSRC icons.qrc)

set(reader_HEADERS
    bookfactory.h
    mainwindow.h
    pageview.h
    contentmodel.h
    contentview.h
    draghelper.h
)

set(reader_SOURCES
    main.cpp
    bookfactory.cpp
    mainwindow.cpp
    pageview.cpp
    contentmodel.cpp
    contentview.cpp
    draghelper.cpp
)

add_executable(reader
    ${reader_SOURCES}
    ${reader_HEADERS}
    ${reader_RSRC}
)

#target_link_libraries(reader ${G3LOG_LIBRARIES})

target_link_libraries(reader Qt5::Core Qt5::Gui Qt5::Widgets)

include_directories(
    ${FUTIL_INCLUDE_DIR}
    ${CLUE_API_INCLUDE_DIR}
)

target_link_libraries(reader
    pdfiumglue
#    djvuglue
)
