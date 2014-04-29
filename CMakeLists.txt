CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
set(CMAKE_LEGACY_CYGWIN_WIN32 0) # is required when CMake < 2.8.4

PROJECT(shdt CXX)

INCLUDE_DIRECTORIES(src src/astro src/lists src/random src/swlib32)
LINK_DIRECTORIES(/usr/local/lib /usr/lib)
ADD_DEFINITIONS(-O3)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

ADD_SUBDIRECTORY(src/astro)
ADD_SUBDIRECTORY(src/check_earthq)
ADD_SUBDIRECTORY(src/getearthq)
ADD_SUBDIRECTORY(src/lists)
ADD_SUBDIRECTORY(src/random)
ADD_SUBDIRECTORY(src/swlib32/unix)
ADD_SUBDIRECTORY(src/qrand)