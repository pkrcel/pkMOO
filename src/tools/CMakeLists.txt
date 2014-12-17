

# The Executables
# - LBX Dump Tool
set(LBXDUMPTOOL "moo1LBXdump")
add_executable(${LBXDUMPTOOL} lbxdump.cpp ${SRC_LBX_LIST})
target_link_libraries(${LBXDUMPTOOL} ${STANDARD_WIN_LIBS})

#message("in Tools:SRC List: ${SRC_LIST}")
