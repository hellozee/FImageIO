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
add_subdirectory(external/libjpeg)
include_directories(include external/libjpeg)
add_subdirectory(src)

# Setting up clang-tidy
find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable"
    )
if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found.")
else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*,-clang-analyzer-alpha.*")
endif()

set_target_properties(
    FImageIO PROPERTIES
    CXX_STANDARD ${CMAKE_CXX_STANDARD}
    CXX_STANDARD_REQUIRED ON
    COMPILE_FLAGS "${WARNING_FLAGS}"
)

if(CLANG_TIDY_EXE)
    set_target_properties(
        FImageIO PROPERTIES
    CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
    )
endif()

# Testing

enable_testing()
file(COPY data DESTINATION .)
add_test(WorkerTests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/worker_tests)


# Documentation

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
