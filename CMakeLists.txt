cmake_minimum_required(VERSION 3.17)
project(PC_semestralka2 C)

set(CMAKE_C_STANDARD 90)

add_executable(PC_semestralka2 main.c algo/graph.h algo/component_finder.h algo/component_finder.c algo/graph.c algo/kruskal_mst.h algo/kruskal_mst.c io/reader_utils.h io/reader_utils.c algo/mst.h algo/mst.c io/edges_io.h io/edges_io.c io/nodes_io.c io/nodes_io.h algo/mrn.c algo/mrn.h)