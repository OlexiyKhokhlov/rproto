cmake_minimum_required(VERSION 2.8)

include(ExternalProject)

ExternalProject_Add(
   pdfium
   GIT_REPOSITORY https://github.com/DrAlexx/pdfium.git
   GIT_TAG light_version
)
