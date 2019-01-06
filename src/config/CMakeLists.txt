# CMakeLists.txt for workers

set(CONFIG_SOURCES
    base.cc
    jpeg.cc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(config STATIC ${CONFIG_SOURCES})
set_target_properties(config PROPERTIES OUTPUT_NAME "fiioconfig")
