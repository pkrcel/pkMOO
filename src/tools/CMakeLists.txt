# Tools Dir specialized CMakeLists file
# this aims to spell all the future "tools" for the PkMOO project.

# The Executables
# - LBX Dump Tool
#   this is the command line tool to extract contents of a Master of Orion
#   LBX container file.
set(LBXDUMPTOOL "moo1LBXdump")
add_executable(${LBXDUMPTOOL} lbxdump.cpp ${SRC_LBX_LIST} ${SRC_UTILS_LIST})
target_link_libraries(${LBXDUMPTOOL} fmt::fmt)

# - LBX Image Viewer
#   this is the Allegro tool to view images in a Master of Orion
#   LBX graphics container file, it will USE Allegro and TGUI2
#   TGUI2 is not installed compiler-wise but locally.
#   current snapshot from <https://www.nooskewl.ca/more/open-source/>

include_directories(${PROJECT_SOURCE_DIR}/tgui2)
set(LBXIMAGEVIEWER "moo1LBXimager")
add_executable(${LBXIMAGEVIEWER} lbximager.cpp ${SRC_LBX_LIST} ${SRC_UTILS_LIST})
target_link_libraries(${LBXIMAGEVIEWER} Allegro::Allegro Allegro::font Allegro::image Allegro::primitives Allegro::color fmt::fmt)
#target_link_libraries(${LBXIMAGEVIEWER} ${STANDARD_WIN_LIBS})

