cmake_minimum_required(VERSION 3.17)
project(PC_semestralka2 C)

set(CMAKE_C_STANDARD 90)

add_executable(PC_semestralka2 main.c graph.h graph.c kruskal_mst.h kruskal_mst.c reader_utils.h reader_utils.c mst.h mst.c edges_io.h edges_io.c nodes_io.c nodes_io.h mrn.c mrn.h console_input.h console_input.c)
target_link_libraries(PC_semestralka2 m)