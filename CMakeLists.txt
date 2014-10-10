cmake_minimum_required(VERSION 2.8)
project(rptoto)

set(CMAKE_VERBOSE_MAKEFILE ON)
message(STATUS "System: " ${CMAKE_SYSTEM_NAME} " " ${CMAKE_SYSTEM_VERSION})
message(STATUS "Processor: " ${CMAKE_HOST_SYSTEM_PROCESSOR})
message(STATUS "CMake generates: " ${CMAKE_GENERATOR})
message(STATUS "Build type:" ${CMAKE_BUILD_TYPE})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)

#Enable C++0x
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wc++0x-compat -Wall -Wextra -pipe -fno-rtti")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -fomit-frame-pointer -march=pentium4 -mtune=pentium4 -flto")
set(CMAKE_LINKER_FLAGS_RELEASE "${CMAKE_LINKER_FLAGS_RELEASE} -s -flto")

#add_subdirectory(lib)
add_subdirectory(reader)
add_subdirectory(lib/futil)
add_subdirectory(lib/pdfium)
