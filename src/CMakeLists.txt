# CMakeList.txt : Primary CMake file for sources of XP++

# Add headers for source files within this folder
target_sources(XP_Plus_Plus
	PUBLIC "${XPPLUSPLUS_INCLUDE_DIR}/XP++/Exceptions/NotImplementedException.hpp"
	PUBLIC "${XPPLUSPLUS_INCLUDE_DIR}/XP++/Planes.hpp"
	PUBLIC "${XPPLUSPLUS_INCLUDE_DIR}/XP++/Message.hpp"
)

# Add sources within this folder
target_sources(XP_Plus_Plus
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Planes.cpp"
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Message.cpp"
)

# Add Subdirectories of this folder
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Plugins")
