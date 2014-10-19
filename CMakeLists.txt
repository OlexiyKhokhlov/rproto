cmake_minimum_required(VERSION 2.8)
project(rproto)

set(CMAKE_VERBOSE_MAKEFILE ON)
message(STATUS "System: " ${CMAKE_SYSTEM_NAME} " " ${CMAKE_SYSTEM_VERSION})
message(STATUS "Processor: " ${CMAKE_HOST_SYSTEM_PROCESSOR})
message(STATUS "CMake generates: " ${CMAKE_GENERATOR})
message(STATUS "Build type:" ${CMAKE_BUILD_TYPE})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)

#Enable C++0x
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wc++0x-compat -Wall -Wextra -pipe -fno-rtti -fvisibility=hidden")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-z,defs")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -fomit-frame-pointer -march=pentium4 -mtune=pentium4 -flto")
set(CMAKE_LINKER_FLAGS_RELEASE "${CMAKE_LINKER_FLAGS_RELEASE} -s -flto")

set(DEBUG_INSTALL_ROOT "${CMAKE_CURRENT_BINARY_DIR}/local_root")

set(FUTIL_INCLUDE_DIR "${DEBUG_INSTALL_ROOT}/include/futil")
set(FUTIL_LIBRARY "${DEBUG_INSTALL_ROOT}/lib/libfutil.a")
set(PDFIUM_INCLUDE_DIR "${DEBUG_INSTALL_ROOT}/include/pdfium")
set(PDFIUM_LIBRARY "${DEBUG_INSTALL_ROOT}/lib/libpdfium.so")
set(CLUE_API_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/clue_api/include")

add_subdirectory(q5_app)
add_subdirectory(lib/futil)
add_subdirectory(lib/clue_api)
add_subdirectory(lib/pdfium)
add_subdirectory(lib/plugins/pdfium)

add_dependencies(clue_api Futil)
add_dependencies(reader Futil clue_api)
