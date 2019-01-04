add_subdirectory(worker)
include_directories(${WORKER_INCLUDE_DIRECTORY} ${CMAKE_CURRENT_SOURCE_DIR})

set(FIIO_SOURCES
    FImageIO.cc)

add_library( FImageIO STATIC ${FIIO_SOURCES} )
target_link_libraries(
    FImageIO
    worker
)
