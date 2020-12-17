cmake_minimum_required(VERSION 3.17)
project(PC_semestralka2 C)

set(CMAKE_C_STANDARD 90)

add_executable(PC_semestralka2 main.c graph.h algo/component_finder.h algo/component_finder.c graph.c algo/kruskal_mst.h algo/kruskal_mst.c reader_utils.h reader_utils.c algo/mst.h algo/mst.c io/edges_io.h io/edges_io.c nodes_io.c nodes_io.h algo/mrn.c algo/mrn.h console_input.h console_input.c)