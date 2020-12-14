cmake_minimum_required(VERSION 3.17)
project(PC_semestralka2 C)

set(CMAKE_C_STANDARD 90)

add_executable(PC_semestralka2 main.c graph.h component_finder.h component_finder.c graph.c kruskal_mst.h kruskal_mst.c reader_utils.h reader_utils.c nodes_reader.h nodes_reader.c edges_reader.h edges_reader.c mst.h mst.c write_edges.h write_edges.c edges_io.h)