#ifndef MST_H
#define MST_H

#include "graph.h"
#include "component_finder.h"
#include "kruskal_mst.h"

int mst(node *nodes, unsigned int nodes_len, edge *edges, unsigned int edges_len, char *output_file);

int join_edges(graph *graphs, unsigned int components, edge **edges, unsigned int *edges_len);

int compare_edges_id(const void *e1, const void *e2);

#endif
