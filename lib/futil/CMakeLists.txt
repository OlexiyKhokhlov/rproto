cmake_minimum_required(VERSION 2.8)

include(ExternalProject)

ExternalProject_Add(
   Futil
   GIT_REPOSITORY https://github.com/DrAlexx/Futils.git
)

