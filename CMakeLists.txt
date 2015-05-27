cmake_minimum_required(VERSION 2.8)
project(rproto)

set(CMAKE_VERBOSE_MAKEFILE ON)
message(STATUS "System: " ${CMAKE_SYSTEM_NAME} " " ${CMAKE_SYSTEM_VERSION})
message(STATUS "Processor: " ${CMAKE_HOST_SYSTEM_PROCESSOR})
message(STATUS "CMake generates: " ${CMAKE_GENERATOR})
message(STATUS "Build type:" ${CMAKE_BUILD_TYPE})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)

set(USE_QT4 ON CACHE BOOL "use Qt4 or Qt5")

set(USE_BINUTILS_WORKAROUND ON CACHE BOOL "use gcc-ar and gcc-ranlib instead ar and ranlib (is needed for LTO)")
if(USE_BINUTILS_WORKAROUND)
    set(CMAKE_AR gcc-ar)
    set(CMAKE_RANLIB gcc-ranlib)
endif(USE_BINUTILS_WORKAROUND)

#Enable C++0x
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wc++0x-compat -Wall -Wextra -pipe -fno-rtti -fvisibility=hidden")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pipe -fvisibility=hidden")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-z,defs")

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0 -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_C_FLAGS_DEBUG "-ggdb -O0 -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS} -fsanitize=address")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -march=native -mtune=native -flto")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2 -march=native -mtune=native -flto")
set(CMAKE_LINKER_FLAGS_RELEASE "${CMAKE_LINKER_FLAGS_RELEASE} -s -flto")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -s -flto")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s -flto")

set(DEBUG_INSTALL_ROOT "${CMAKE_CURRENT_BINARY_DIR}/local_root")

set(UTF8_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/utf8")
set(FUTIL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/")
set(CLUE_API_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/glue_api/include")

set(BOSS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/BOSS/boss/include")

add_subdirectory(q5_app)

add_subdirectory(lib/glue_api)
add_subdirectory(lib/plugins/pdfium)
#add_subdirectory(lib/plugins/djvulibre)

add_dependencies(pdfiumglue glue_api)
#add_dependencies(djvuglue glue_api)
add_dependencies(reader glue_ap)
