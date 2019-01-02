# CMakeLists.txt for workers
set(WORKER_SOURCES
    jpeg.cc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(worker STATIC ${WORKER_SOURCES})
set_target_properties(worker PROPERTIES OUTPUT_NAME "FImageIO_worker")
target_link_libraries(
    worker
    libjpeg
)


set(WORKER_TEST_SOURCES 
    tests/jpeg_test.cc
)

add_executable(worker_tests ${WORKER_TEST_SOURCES})
target_link_libraries(
    worker_tests
    worker
)
