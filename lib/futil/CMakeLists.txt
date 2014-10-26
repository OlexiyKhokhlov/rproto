cmake_minimum_required(VERSION 2.8)

include(ExternalProject)

ExternalProject_Add(
   Futil
#   GIT_REPOSITORY https://github.com/DrAlexx/Futils.git
   GIT_REPOSITORY /home/forth/work/libs/Futils
   CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${DEBUG_INSTALL_ROOT}
   UPDATE_COMMAND git pull
)

