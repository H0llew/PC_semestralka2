#ifndef MRN_H
#define MRN_H

#include <math.h>
#include <stdlib.h>
#include "../graph.h"
#include "../kruskal_mst.h"
#include "../edges_io.h"

int mrn(char *file_name, node *nodes, unsigned int nodes_len);

graph *create_complete_graph(node *nodes, unsigned int nodes_len);

double get_distance(double longitude_a, double latitude_a, double longitude_b, double latitude_b);

double degrees_to_radians(double x);

int attach_edges_info(edge *edges, unsigned int edges_len, node *nodes, unsigned int nodes_len);

#endif
