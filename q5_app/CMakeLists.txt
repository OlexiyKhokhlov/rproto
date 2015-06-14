CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#find_package(g3log REQUIRED)
#include_directories(${G3LOG_INCLUDE_DIRS})

if(USE_QT4)
    find_package(Qt4 REQUIRED)
    INCLUDE(${QT_USE_FILE})
    ADD_DEFINITIONS(${QT_DEFINITIONS})
else(USE_QT4)
    find_package(Qt5Core REQUIRED)
    find_package(Qt5Gui REQUIRED)
    find_package(Qt5Widgets REQUIRED)
endif(USE_QT4)

set(reader_HEADERS
    bookfactory.h
    mainwindow.h
    pageview.h
    contentmodel.h
    contentview.h
)

set(reader_SOURCES
    main.cpp
    bookfactory.cpp
    mainwindow.cpp
    pageview.cpp
    contentmodel.cpp
    contentview.cpp
)

add_executable(reader ${reader_SOURCES} ${reader_HEADERS})

#target_link_libraries(reader ${G3LOG_LIBRARIES})

if(USE_QT4)
    target_link_libraries(reader ${QT_LIBRARIES})
else(USE_QT4)
    qt5_use_modules(reader Core Gui Widgets)
endif(USE_QT4)

include_directories(
    ${FUTIL_INCLUDE_DIR}
    ${BOSS_INCLUDE_DIR}
    ${CLUE_API_INCLUDE_DIR}
)

target_link_libraries(reader
    pdfiumglue
#    djvuglue
)
