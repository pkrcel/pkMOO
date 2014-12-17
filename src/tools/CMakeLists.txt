# Tools Dir specialized CMakeLists file
# this aims to spell all the future "tools" for the PkMOO project.

# The Executables
# - LBX Dump Tool
#   this is the command line tool to extract contents of a Master of Orion
#   LBX container file.
set(LBXDUMPTOOL "moo1LBXdump")
add_executable(${LBXDUMPTOOL} lbxdump.cpp ${SRC_LBX_LIST})
target_link_libraries(${LBXDUMPTOOL} ${STANDARD_WIN_LIBS})

#message("in Tools:SRC List: ${SRC_LIST}")
