project(moo1LBXhandler)
cmake_minimum_required(VERSION 2.8)

# version numbers
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 1)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel"
      FORCE)
endif()

# source directories
aux_source_directory(src SRC_LIST)

# add the binary tree to the search path for include files
# so that we will eventually find Cmake Generated Headers
include_directories("${PROJECT_BINARY_DIR}")

#add library TGUI2 in project
add_subdirectory(tgui2)
include_directories(${PROJECT_SOURCE_DIR}/tgui2)

# add include directories
include_directories(${PRJ_INCLUDE_DIR})

#prepare resource data directory
#file(GLOB_RECURSE RESOURCES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/_Resources"
#    background/*.png
#    fonts/*.ttf
#    GFX/*.png
#    sound/*.ogg
#    )


# set standard libs
set(STANDARD_WIN_LIBS kernel32 user32 gdi32 winspool shell32 ole32 oleaut32 uuid comdlg32 advapi32 winmm psapi shlwapi)
#set(ALLEGRO_LIBS allegro-debug-static allegro_dialog-debug-static allegro_audio-debug-static allegro_acodec-debug-static allegro_primitives-debug-static allegro_font-debug-static allegro_ttf-debug-static allegro_image-debug-static allegro_color-debug-static)
set(ALLEGRO_LIBS allegro-debug allegro_dialog-debug allegro_audio-debug allegro_acodec-debug allegro_primitives-debug allegro_font-debug allegro_ttf-debug allegro_image-debug allegro_color-debug)
#set(ALLEGRO_LIBS allegro_monolith)
set(DEP_ALLEG_LIBS ogg opengl32)

# set include dirs
set(TGUI2_INCLUDE_DIR "tgui2")

# set c++11 flags
set(CMAKE_CXX_FLAGS "-std=c++11 -static-libstdc++ -mwindows")

#the executable
add_executable(${PROJECT_NAME} ${SRC_LIST} ${RESOURCES})
#add_dependencies(${PROJECT_NAME} copy_resources)

#add_custom_command(
#            TARGET ${PROJECT_NAME}
#            COMMAND "${CMAKE_COMMAND}" -E copy_directory
#                    "${PROJECT_SOURCE_DIR}/Resources" "${PROJECT_BINARY_DIR}/Resources"
#            )


#target link
target_link_libraries(${PROJECT_NAME} TGUI2)
target_link_libraries(${PROJECT_NAME} ${ALLEGRO_LIBS})
target_link_libraries(${PROJECT_NAME} ${DEP_ALLEG_LIBS})
target_link_libraries(${PROJECT_NAME} ${STANDARD_WIN_LIBS})

