cmake_minimum_required(VERSION 3.2)

include(ExternalProject)

ExternalProject_Add(
   pdfium
   GIT_REPOSITORY https://github.com/OlexiyKhokhlov/pdfium.git
   GIT_TAG light_version
   UPDATE_COMMAND git pull
   CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_CXX_FLAGS_DEBUG=${CMAKE_CXX_FLAGS_DEBUG}
    -DCMAKE_C_FLAGS_DEBUG=${CMAKE_C_FLAGS_DEBUG}
    -DCMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}
    -DCMAKE_C_FLAGS_RELEASE=${CMAKE_C_FLAGS_RELEASE}
    -DCMAKE_INSTALL_PREFIX:PATH=${DEBUG_INSTALL_ROOT}
    -DUSE_BINUTILS_WORKAROUND=${USE_BINUTILS_WORKAROUND}
    -DUSE_SYSTEM_FREETYPE=${USE_SYSTEM_FREETYPE}
    -DUSE_SYSTEM_JPEG=${USE_SYSTEM_JPEG}
    -DUSE_SYSTEM_ZLIB=${USE_SYSTEM_ZLIB}
    -DUSE_SYSTEM_LCMS2=${USE_SYSTEM_LCMS2}
    -DUSE_SYSTEM_OPENJPEG=${USE_SYSTEM_OPENJPEG}
    -DUSE_GB1_MAPS=${USE_GB1_MAPS}
    -DUSE_CNS1_MAPS=${USE_CNS1_MAPS}
    -DUSE_JAPAN1_MAPS=${USE_JAPAN1_MAPS}
    -DUSE_KOREA_MAPS=${USE_KOREA_MAPS}
)

