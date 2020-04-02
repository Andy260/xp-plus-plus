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

# Define common CMake utility files
set(XPPLUSPLUS_UTILITY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
# Define project include directory
set(XPPLUSPLUS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
# Define project source directory
set(XPPLUSPLUS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
# Define project tests directory
set(XPPLUSPLUS_TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")

# Set-up modules
include(FetchContent)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${XPPLUSPLUS_UTILITY_DIR})
include("${XPPLUSPLUS_UTILITY_DIR}/FetchMarco.cmake.in")

# X-Plane SDK
if (XPLANE_SDK_DIR OR DEFINED ENV{XPLANE_SDK_DIR} OR DEFINED ENV{XPLANE_SDK_DIR} OR DEFINED ENV{XPLANE_SDK_DIR})
		# X-Plane SDK path set by user or env var
else()
	set(XPLANE_SDK_DIR "" CACHE PATH "Path to the latest X-Plane SDK")
	message(WARNING "XPLANE_SDK_DIR variable is missing.  Please set this variable to specify path to the latest X-Plane SDK")
endif()

# Add Project sources
add_subdirectory("${XPPLUSPLUS_SOURCE_DIR}")

# Add X-Plane SDK
add_compile_definitions(XPLM200 XPLM210 XPLM300 XPLM301)
# Windows Specific
if (WIN32)
	# Preprocessor defines
	add_compile_definitions(IBM)

	# Visual Studio compilers have deprecated strcpy
	if (MSVC)
		add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
	endif(MSVC)
# MAC specific
elseif (APPLE)
	# Preprocessor defines
	link_directories("${XPLANE_SDK_DIR}/Libraries/Mac")
	add_compile_definitions(APL)
# Linux specific
elseif (UNIX AND NOT APPLE)
	# Preprocessor defines
	link_directories("${XPLANE_SDK_DIR}/Libraries/Mac")
	add_compile_definitions(LIN)
endif()
