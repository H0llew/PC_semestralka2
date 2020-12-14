cmake_minimum_required(VERSION 3.17)
project(PC_semestralka2 C)

set(CMAKE_C_STANDARD 90)

add_executable(PC_semestralka2 main.c graph.h component_finder.h component_finder.c graph.c kruskal_mst.h kruskal_mst.c reader_utils.h reader_utils.c mst.h mst.c io/edges_io.h io/edges_io.c io/nodes_io.c io/nodes_io.h)