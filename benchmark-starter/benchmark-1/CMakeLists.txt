add_library(benchmark1
        source/benchmark-1.c
        source/file-state.c
        source/heap-lib.c
        ../common/source/utils.c
)
target_include_directories(benchmark1 PUBLIC include)
target_link_libraries(benchmark1 PRIVATE common)
target_include_directories(benchmark1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common/include)