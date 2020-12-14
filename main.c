#include <stdio.h>

#include "graph.h"
#include "nodes_reader.h"
#include "component_finder.h"
#include "kruskal_mst.h"
#include "mst.h"
#include "write_edges.h"

int main(int argc, char *argv[]) {
    unsigned int i, j;
    int res;
    /* --- */
    edge *edges = NULL;
    unsigned int edges_len, neighbours_len;
    unsigned int *neighbours = NULL;
    /* --- */
    node *nodes = NULL;
    unsigned int nodes_len;
    /* --- */
    unsigned int *mark = NULL;
    /* --- */
    graph *graphs = NULL;
    unsigned int graphs_len = 0; /* AKA počet komponent */

    printf("Hello, World!\n");

    /* GROUP */
    /*
    edges = malloc(sizeof(edge) * 6);
    edges_len = 6;
     */
    /* --- */
    /*
    edges[0] = create_edge(1, 1, 3, 10);
    edges[1] = create_edge(2, 2, 1, 30);
    edges[2] = create_edge(3, 3, 2, 20);
    edges[3] = create_edge(4, 2, 3, 20);
    edges[4] = create_edge(5, 3, 40, 9000);
    edges[5] = create_edge(6, 40, 2, 20);
     */
    /* END OF GROUP */

    /* GROUP */
    /*
    nodes = malloc(sizeof(edge) * 6);
    nodes_len = 6;
     */
    /* --- */
    /*
    nodes[0] = create_node(1, 0, 0);
    nodes[1] = create_node(2, 0, 0);
    nodes[2] = create_node(3, 0, 0);
    nodes[3] = create_node(20, 0, 0);
    nodes[4] = create_node(21, 0, 0);
    nodes[5] = create_node(40, 0, 0);
     */
    /* END OF GROUP */

    /*
    mark = malloc(sizeof(int) * nodes_len);
    for (i = 0; i < nodes_len; ++i) {
        mark[i] = 0;
    }

    res = find_components(nodes, nodes_len, edges, edges_len);
    graphs = create_graphs(nodes, nodes_len, edges, edges_len, res);
    for (i = 0; i < res; ++i) {
        for (j = 0; j < graphs[i].e; ++j)
            printf("A: %d \n", graphs[i].edges[j].id);
    }
    do_msts(graphs, res, nodes, nodes_len);
    for (i = 0; i < res; ++i) {
        for (j = 0; j < (graphs[i].v - 1); ++j)
            printf("T: %d \n", graphs[i].mst[j].id);
    }
    */

    nodes_len = 0;
    edges_len = 0;

    read_nodes(argv[1], &nodes, &nodes_len);
    read_edges(argv[2], &edges, &edges_len);

    mst(nodes, nodes_len, edges, edges_len, argv[3]);
    /* create_edges_file(argv[3], edges, edges_len); */

    return 0;
}

int mainXX(int argc, char *argv[]) {
    int err = 0;

    node *nodes = NULL;
    unsigned int nodes_len = 0;

    read_nodes(argv[1], &nodes, &nodes_len);

    return 0;
}
