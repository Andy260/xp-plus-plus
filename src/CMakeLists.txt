# CMakeList.txt : Primary CMake file for sources of XP++

# Add library to build
add_library(XPPlusPlus STATIC)

# Add Project and X-Plane SDK includes
target_include_directories(XPPlusPlus
	PUBLIC "${XPPLUSPLUS_INCLUDE_DIR}"
	PRIVATE  "${XPLANE_SDK_DIR}/CHeaders/XPLM"
	PRIVATE  "${XPLANE_SDK_DIR}/CHeaders/Widgets"
)

# Add headers for source files within this folder
target_sources(XPPlusPlus
	PUBLIC "${XPPLUSPLUS_INCLUDE_DIR}/XP++/DataAccess.hpp"
	PUBLIC "${XPPLUSPLUS_INCLUDE_DIR}/XP++/DataAccess/DataRef.hpp"
	PUBLIC "${XPPLUSPLUS_INCLUDE_DIR}/XP++/DataAccess/DataRefType.hpp"
	PUBLIC "${XPPLUSPLUS_INCLUDE_DIR}/XP++/DataAccess/UserDataRef.hpp"
	PUBLIC "${XPPLUSPLUS_INCLUDE_DIR}/XP++/Exceptions/NotImplementedException.hpp"
	PUBLIC "${XPPLUSPLUS_INCLUDE_DIR}/XP++/Exceptions/XPException.hpp"
	PUBLIC "${XPPLUSPLUS_INCLUDE_DIR}/XP++/UI/Menu.hpp"
	PUBLIC "${XPPLUSPLUS_INCLUDE_DIR}/XP++/UI/MenuItem.hpp"
	PUBLIC "${XPPLUSPLUS_INCLUDE_DIR}/XP++/UI/Menus.hpp"
	PUBLIC "${XPPLUSPLUS_INCLUDE_DIR}/XP++/Planes.hpp"
	PUBLIC "${XPPLUSPLUS_INCLUDE_DIR}/XP++/Processing.hpp"
	PUBLIC "${XPPLUSPLUS_INCLUDE_DIR}/XP++/Message.hpp"
	PUBLIC "${XPPLUSPLUS_INCLUDE_DIR}/XP++/UserPlugin.hpp"
)

# Add sources within this folder
target_sources(XPPlusPlus
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/DataAccess/DataRef.cpp"
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/DataAccess/DataRefType.cpp"
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/DataAccess/UserDataRef.cpp"
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/UI/Menu.cpp"
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/UI/MenuItem.cpp"
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Planes.cpp"
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Message.cpp"
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/UserPlugin.cpp"
)

# SDK library linking and pre-processor defines
add_compile_definitions(XPLM200 XPLM210 XPLM300 XPLM301)
if (WIN32)
	add_compile_definitions(IBM)

	target_link_libraries(XPPlusPlus 
	"${XPLANE_SDK_DIR}/Libraries/Win/XPLM_64.lib"
	"${XPLANE_SDK_DIR}/Libraries/Win/XPWidgets_64.lib" 
	"OpenGL32.lib"
	)
	
	# Visual Studio compilers have deprecated strcpy
	if (MSVC)
		add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
	endif(MSVC)
elseif (APPLE)
	link_directories("${XPLANE_SDK_DIR}/Libraries/Mac")
	add_compile_definitions(APL)
	# TODO: Link X-Plane SDK libraries on Mac platform
elseif (UNIX AND NOT APPLE)
	link_directories("${XPLANE_SDK_DIR}/Libraries/Mac")
	add_compile_definitions(LIN)
	# TODO: Link X-Plane SDK libraries on Linux platform
endif()

# Add Subdirectories of this folder
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Plugins")
