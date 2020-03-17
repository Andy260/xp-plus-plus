# CMakeList.txt : Primary CMake file for XP++

cmake_minimum_required (VERSION 3.12 FATAL_ERROR)

# Set-up project
project(XP++ CXX C)
# Specify and require C++11 with no extensions
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set Project version project version
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

option(BUILD_TESTS "Build Unit Tests" FALSE)

# Define project include directory
set(XPPLUSPLUS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
# Define project source directory
set(XPPLUSPLUS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
# Define project tests directory
set(XPPLUSPLUS_TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")

# X-Plane SDK
if (XPLANE_SDK_DIR OR DEFINED ENV{XPLANE_SDK_DIR} OR DEFINED ENV{XPLANE_SDK_DIR} OR DEFINED ENV{XPLANE_SDK_DIR})
		# X-Plane SDK path set by user or env var
else()
	set(XPLANE_SDK_DIR "" CACHE PATH "Path to the latest X-Plane SDK")
	message(WARNING "XPLANE_SDK_DIR variable is missing.  Please set this variable to specify path to the latest X-Plane SDK")
endif()

# Add plugin to build
add_library(XP_Plus_Plus STATIC)

# Add Project and X-Plane SDK includes
target_include_directories(XP_Plus_Plus
	PRIVATE "${XPPLUSPLUS_INCLUDE_DIR}"
	PUBLIC  "${XPLANE_SDK_DIR}/CHeaders/XPLM"
	PUBLIC  "${XPLANE_SDK_DIR}/CHeaders/Widgets"
)

# Add Project sources
add_subdirectory("${XPPLUSPLUS_SOURCE_DIR}")

if (BUILD_TESTS)
	add_subdirectory("${XPPLUSPLUS_TEST_DIR}")
endif()

# Add X-Plane SDK
#add_definitions(-DXPLM200 -DXPLM210 -DXPLM300 -DXPLM301)
add_compile_definitions(XPLM200 XPLM210 XPLM300 XPLM301)
# Windows Specific
if (WIN32)
	# Preprocessor defines
	#add_definitions(-DIBM -D_CRT_SECURE_NO_WARNINGS)
	add_compile_definitions(IBM)

	# Visual Studio compilers have deprecated strcpy
	if (MSVC)
		add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
	endif(MSVC)

	# SDK library linking
	target_link_libraries(XP_Plus_Plus 
		"${XPLANE_SDK_DIR}/Libraries/Win/XPLM_64.lib"
		"${XPLANE_SDK_DIR}/Libraries/Win/XPWidgets_64.lib" 
		"OpenGL32.lib"
	)
# MAC specific
elseif (APPLE)
	# Preprocessor defines
	link_directories("${XPLANE_SDK_DIR}/Libraries/Mac")
	#add_definitions(-DAPL)
	add_compile_definitions(APL)
# Linux specific
elseif (UNIX AND NOT APPLE)
	# Preprocessor defines
	link_directories("${XPLANE_SDK_DIR}/Libraries/Mac")
	#add_definitions(-DLIN)
	add_compile_definitions(LIN)
endif()

set_target_properties(XP_Plus_Plus
					  PROPERTIES 
					  OUTPUT_NAME "XP++"
)
