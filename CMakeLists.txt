project(pkMOO CXX)
cmake_minimum_required(VERSION 3.0)

# version numbers
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 1)

#set the build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING
      "Choose the type of build, options are:
        None Debug Release RelWithDebInfo MinSizeRel"
      FORCE)
endif()

# Collect manually BUT RECURSIVELY sources in directories.
# NOTE: this as well as file globbing is DISCOURAGED by the cmake dev team in
# countless places on the web (!)
# BUT: I can't be arsed to type singularly all source files...sorry!
# This means that when in doubt CMAKE has to be re-run MANUALLY cause the check
# in the makefile for a changed CMakeLists file would fail and something wonky
# may happen during build.

 aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
 aux_source_directory(${PROJECT_SOURCE_DIR}/src/lbx SRC_LBX_LIST)
 aux_source_directory(${PROJECT_SOURCE_DIR}/src/tools SRC_TOOLS_LIST)
 aux_source_directory(${PROJECT_SOURCE_DIR}/src/utils SRC_UTILS_LIST)

# set(GLOB_SOURCE ${SRC_LIST} ${SRC_ERROR_LIST} ${SRC_LBX_LIST} ${SRC_TOOLS_LIST}
#                 ${SRC_UTILS_LIST})

# add the binary tree to the search path for include files
# so that we will eventually find Cmake Generated Headers
include_directories("${PROJECT_BINARY_DIR}")


#...and 'classic' include paths (AZ ordered !)
include_directories(${PROJECT_SOURCE_DIR}/src/error)
include_directories(${PROJECT_SOURCE_DIR}/src/lbx)
include_directories(${PROJECT_SOURCE_DIR}/src/tools)
include_directories(${PROJECT_SOURCE_DIR}/src/utils)

#prepare resource data directory
#file(GLOB_RECURSE resources RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/_Resources"
#    background/*.png
#    fonts/*.ttf
#    GFX/*.png
#    sound/*.ogg
#    )

# set standard libs (still for WIndows only)
 set(STANDARD_WIN_LIBS kernel32 user32 gdi32 winspool shell32 ole32 oleaut32
                      uuid comdlg32 advapi32 winmm psapi shlwapi)


# find used libs in modern CMAKE fashion
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/../CMake/modules/Allegro)
find_package(Allegro REQUIRED)
find_package(fmt REQUIRED)

# set c++20 flags
# we use with C++20 standard features when possible and statically link
# the std libs (to ease distribution)
# NOTE: this might still inject a dependency to libwinpthreads on Windows
# to avoid that use a NON-posix threads enabled compiler.
# some handy g++ switches, we are still on windows only, do not use -mwindows as it redirects 
# stdout somewhere else from the console.

set(CMAKE_CXX_FLAGS "-g -O0") #-std=c++20 -static-libstdc++ -static-libgcc

# adding Tools subdir in which there's something to build
add_subdirectory(${PROJECT_SOURCE_DIR}/src/tools)

#message("In ROOT  - Global SRC List: ${GLOB_SOURCE}")
