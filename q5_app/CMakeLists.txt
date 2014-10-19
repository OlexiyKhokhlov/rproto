CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(g3log REQUIRED)
include_directories(${G3LOG_INCLUDE_DIRS})

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(reader_HEADERS
    mainwindow.h
    pageview.h
)

set(reader_SOURCES
    main.cpp
    mainwindow.cpp
    pageview.cpp
)

add_executable(reader ${reader_SOURCES} ${reader_HEADERS})

target_link_libraries(reader ${G3LOG_LIBRARIES})
qt5_use_modules(reader Core Gui Widgets)

include_directories(${FUTIL_INCLUDE_DIR})
