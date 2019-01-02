cmake_minimum_required(VERSION 3.0)

# Initial Setup

set(PROJECT_NAME FImageIO)
project(${PROJECT_NAME})
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

if( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
      # using clang
      set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Weverything")
    elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
      # using gcc
      set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wextra")
    elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Intel")
      # using intel c compiler
    elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
      # using visual studio c compiler
    endif()
endif()

set(CMAKE_CXX_STANDARD 17)

include_directories(include libjpeg_SOURCE_DIR)
add_subdirectory(src)
add_subdirectory(external/jpeg-9c)

if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
	option(BUILD_DOC "Build documentation" ON)
	set(DOXYGEN_SKIP_DOT false)

	find_package(Doxygen)
	if (DOXYGEN_FOUND)

	    set(DOXYGEN_IN docs/Doxyfile.in)
	    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/docs/Doxyfile)

	    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

	    add_custom_target( docs ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		VERBATIM )

	else (DOXYGEN_FOUND)
	  message("Doxygen not installed")
	endif (DOXYGEN_FOUND)
endif()
