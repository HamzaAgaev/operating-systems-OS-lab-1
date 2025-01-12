add_library(benchmark2
        source/benchmark-2.c
)
target_include_directories(benchmark2 PUBLIC include)
target_link_libraries(benchmark2 PRIVATE common)
target_include_directories(benchmark2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common/include)