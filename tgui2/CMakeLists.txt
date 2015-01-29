
set(TGUI2_SOURCES tgui2.cpp tgui2_widgets.cpp)

add_library(tgui2 STATIC ${TGUI2_SOURCES})
set_target_properties(tgui2
	PROPERTIES
	OUTPUT_NAME tgui2
	)
