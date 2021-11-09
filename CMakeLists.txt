cmake_minimum_required(VERSION 3.2)
project(rproto)

set(CMAKE_VERBOSE_MAKEFILE ON)
message(STATUS "System: " ${CMAKE_SYSTEM_NAME} " " ${CMAKE_SYSTEM_VERSION})
message(STATUS "Processor: " ${CMAKE_HOST_SYSTEM_PROCESSOR})
message(STATUS "CMake generates: " ${CMAKE_GENERATOR})
message(STATUS "Build type:" ${CMAKE_BUILD_TYPE})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wc++20-compat -Wall -Wextra -pipe -fno-rtti -fvisibility=hidden")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pipe -fvisibility=hidden")

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0 -fno-omit-frame-pointer")
set(CMAKE_C_FLAGS_DEBUG "-ggdb -O0 -fno-omit-frame-pointer")

set(CMAKE_LINKER_FLAGS_RELEASE "${CMAKE_LINKER_FLAGS_RELEASE} -s ")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -s ")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s ")

if(WIN32)
  add_definitions(-D_WIN32)
  set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2 -march=pentium4 -mtune=pentium4 ")
  set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -O2 -march=pentium4 -mtune=pentium4 ")
  set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} ")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
else(WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -pthread")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -pthread")

  set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2 -march=native -mtune=native -flto")
  set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -O2 -march=native -mtune=native -flto")
  set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -flto ")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto ")

  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -Wl,-z,defs")

  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address")
  set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS} -fsanitize=address")
endif(WIN32)

set(DEBUG_INSTALL_ROOT "${CMAKE_CURRENT_BINARY_DIR}/local_root")

set(UTF8_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/utf8")
set(FUTIL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/")
set(CLUE_API_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/glue_api/include")

add_subdirectory(q5_app)

add_subdirectory(lib/glue_api)
add_subdirectory(lib/plugins/pdfium)
#add_subdirectory(lib/plugins/djvulibre)

add_dependencies(pdfiumglue glue_api)
#add_dependencies(djvuglue glue_api)
add_dependencies(reader glue_api)
