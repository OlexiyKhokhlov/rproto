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

#Enable C++0x
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wc++0x-compat -Wall -Wextra -pipe -fno-rtti -fvisibility=hidden")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pipe -fvisibility=hidden")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-z,defs")

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0 -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_C_FLAGS_DEBUG "-ggdb -O0 -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS} -fsanitize=address")

set(CMAKE_CXX_FLAGS_RELEASE "-O2 -fomit-frame-pointer -march=native -mtune=native -flto")
set(CMAKE_C_FLAGS_RELEASE "-O2 -fomit-frame-pointer -march=native -mtune=native -flto")
set(CMAKE_LINKER_FLAGS_RELEASE "${CMAKE_LINKER_FLAGS_RELEASE} -s -flto")

set(DEBUG_INSTALL_ROOT "${CMAKE_CURRENT_BINARY_DIR}/local_root")

set(FUTIL_INCLUDE_DIR "${DEBUG_INSTALL_ROOT}/include/futil")
set(FUTIL_LIBRARY "${DEBUG_INSTALL_ROOT}/lib/libfutil.a")
set(CLUE_API_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/clue_api/include")

add_subdirectory(q5_app)
add_subdirectory(lib/futil)
add_subdirectory(lib/clue_api)
add_subdirectory(lib/plugins/pdfium)
add_subdirectory(lib/plugins/djvulibre)

add_dependencies(glue_api Futil)
add_dependencies(pdfiumglue Futil glue_api)
add_dependencies(djvuglue Futil glue_api)
add_dependencies(reader Futil glue_api pdfiumglue)
