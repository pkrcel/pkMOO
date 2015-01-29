# Tools Dir specialized CMakeLists file
# this aims to spell all the future "tools" for the PkMOO project.

# The Executables
# - LBX Dump Tool
#   this is the command line tool to extract contents of a Master of Orion
#   LBX container file.
set(LBXDUMPTOOL "moo1LBXdump")
add_executable(${LBXDUMPTOOL} lbxdump.cpp ${SRC_LBX_LIST} ${SRC_UTILS_LIST})
target_link_libraries(${LBXDUMPTOOL} ${STANDARD_WIN_LIBS})

# - LBX Image Viewer
#   this is the Allegro tool to view images in a Master of Orion
#   LBX graphics container file.
set(LBXIMAGEVIEWER "moo1LBXimager")
add_executable(${LBXIMAGEVIEWER} lbximager.cpp ${SRC_LBX_LIST} ${SRC_UTILS_LIST})
target_link_libraries(${LBXIMAGEVIEWER} ${ALLEGRO_LIBS})
target_link_libraries(${LBXIMAGEVIEWER} ${DEP_ALLEG_LIBS})
target_link_libraries(${LBXIMAGEVIEWER} ${STANDARD_WIN_LIBS})

message("in Tools: LIBS List: ${ALLEGRO_LIBS}")
