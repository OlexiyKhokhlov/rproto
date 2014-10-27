cmake_minimum_required(VERSION 2.8)

include(ExternalProject)

ExternalProject_Add(
   pdfium
   GIT_REPOSITORY https://github.com/DrAlexx/pdfium.git
#   GIT_REPOSITORY /home/forth/work/libs/pdfium
   GIT_TAG light_version
   UPDATE_COMMAND git pull
   CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} 
    -DCMAKE_CXX_FLAGS_DEBUG=${CMAKE_CXX_FLAGS_DEBUG}
    -DCMAKE_C_FLAGS_DEBUG=${CMAKE_C_FLAGS_DEBUG}
    -DCMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}
    -DCMAKE_C_FLAGS_RELEASE=${CMAKE_C_FLAGS_RELEASE}
    -DCMAKE_INSTALL_PREFIX:PATH=${DEBUG_INSTALL_ROOT}
)
