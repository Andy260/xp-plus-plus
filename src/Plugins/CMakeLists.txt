# CMakeList.txt : PCMake file for Plugin related sources of XP++

# Add headers for source files within this folder
target_sources(XPPlusPlus
	PRIVATE "${XPPLUSPLUS_INCLUDE_DIR}/XP++/Plugins/Plugin.hpp"
	PRIVATE "${XPPLUSPLUS_INCLUDE_DIR}/XP++/Plugins/Plugins.hpp"
	PRIVATE "${XPPLUSPLUS_INCLUDE_DIR}/XP++/Plugins/PluginID.hpp"
	PRIVATE "${XPPLUSPLUS_INCLUDE_DIR}/XP++/Plugins/PluginInfo.hpp"
)

# Add sources within this folder
target_sources(XPPlusPlus
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Plugin.cpp"
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Plugins.cpp"
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/PluginID.cpp"
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/PluginInfo.cpp"
)
