cmake_minimum_required(VERSION 4.4.0)
include(FetchContent)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")
set(CMAKE_CXX_MODULE_STD 1)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_SCAN_FOR_MODULES TRUE)

project(LatticeCxxPlugin
    VERSION 0.1
    DESCRIPTION "A C/C++ Plugin for Lattice"
    HOMEPAGE_URL "https://github.com/proatgram/lattice-cxx"
    LANGUAGES CXX
)

FetchContent_Declare(
  lattice
  GIT_REPOSITORY file:///home/thetimbrick/Projects/Lattice
  GIT_TAG        main
)

FetchContent_MakeAvailable(lattice)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(src)
