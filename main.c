#include <stdio.h>
#include <stdlib.h>

#include "console_input.h"
#include "graph.h"
#include "nodes_io.h"
#include "edges_io.h"
#include "mst.h"
#include "mrn.h"

#define INPUT_ERROR "Input error!\n"
#define READ_ERROR "Error while reading files!n"
#define V_ERROR "Invalid vertex file.\n"
#define E_ERROR "Invalid edge file.\n"
#define MST_ERROR "Error while performing -mst!"
#define MRN_ERROR "Error while performing -mrn!"

void mainXXXXXX(int argc, char *argv[]) {
    /*
    unsigned int i, j;
    int res;*/
    /* --- */
    /*edge *edges = NULL;
    unsigned int edges_len, neighbours_len;
    unsigned int *neighbours = NULL;*/
    /* --- */
    /*node *nodes = NULL;
    unsigned int nodes_len;*/
    /* --- */
    /*unsigned int *mark = NULL;
     --- */
    /*
    graph *graphs = NULL;*//*
    unsigned int graphs_len = 0;*/ /* AKA počet komponent */

    /*
    printf("Hello, World!\n");
     */
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

    /*
    nodes_len = 0;
    edges_len = 0;

    read_nodes(argv[1], &nodes, &nodes_len);
    read_edges(argv[2], &edges, &edges_len);

    mst(nodes, nodes_len, edges, edges_len, argv[3]);
     */
    /* create_edges_file(argv[3], edges, edges_len); */

    /*
    return 0;
     */
}

void mainXX(int argc, char *argv[]) {
    /*
    int err = 0;

    node *nodes = NULL;
    unsigned int nodes_len = 0;

    read_nodes(argv[1], &nodes, &nodes_len);

    return 0;
     */
}

void mainaaaa(int argc, char *argv[]) {

    /*
    edge *edges = NULL;
    unsigned int edges_len = 0, i;

    node *nodes = NULL;
    unsigned int nodes_len = 0;

    graph *res = NULL;

    read_edges(argv[1], &edges, &edges_len);
    read_nodes(argv[2], &nodes, &nodes_len);

    mrn(argv[4], nodes, nodes_len);

    return 0;
     */
}

int main(int argc, char *argv[]) {
    unsigned int i;
    /* vstup z konzole */
    int *flags_val = NULL;
    unsigned int flags_len = 4;
    char *flags[] = {"-v", "-e", "-mst", "-mrn"};
    /* vrcholy a hrany */
    unsigned int read_err = 0;
    node *nodes = NULL;
    edge *edges = NULL;
    unsigned int nodes_len, edges_len;
    /* mst a mrn */
    int res;

    graph *g = NULL;

    /* zpracuj vstup z konzole */
    flags_val = get_input_indexes(argc, argv, flags_len, flags);
    if (!flags_val) {
        printf(INPUT_ERROR);
        return EXIT_FAILURE;
    }

    /* zkontrolu zda byl zadán alespoň 1 nepovinný přepínač */
    if (flags_val[2] == 0 && flags_val[3] == 0) {
        free(flags_val);
        return EXIT_SUCCESS;
    }

    /* načti vrcholy */
    if (flags_val[0] == 0) {
        printf(V_ERROR);
        free(flags_val);
        return 1;
    } else {
        read_err = read_nodes(argv[flags_val[0]], &nodes, &nodes_len);
        if (read_err == 1) {
            free(flags_val);
            printf(V_ERROR);
            return 1;
        }
        if (read_err == 2) {
            free(flags_val);
            printf(READ_ERROR);
            return EXIT_FAILURE;
        }
    }

    /* načti hrany */
    if (flags_val[1] == 0) {
        printf(E_ERROR);
        free(flags_val);
        free_nodes(&nodes, nodes_len);
        return 2;
    } else {
        read_err = read_edges(argv[flags_val[1]], &edges, &edges_len);
        if (read_err == 1) {
            free(flags_val);
            free_nodes(&nodes, nodes_len);
            printf(E_ERROR);
            return 2;
        }
        if (read_err == 2) {
            free(flags_val);
            free_nodes(&nodes, nodes_len);
            printf(READ_ERROR);
            return EXIT_FAILURE;
        }
    }

    /* proveď mst */
    if (flags_val[2] != 0) {
        res = mst(nodes, nodes_len, edges, edges_len, argv[flags_val[2]]);
        if (res == -1) {
            free(flags_val);
            free_nodes(&nodes, nodes_len);
            free_edges(&edges, edges_len);
            printf(MST_ERROR);
            return EXIT_FAILURE;
        }
    }

    /* proveď mrn */
    if (flags_val[3] != 0) {
        res = mrn(nodes, nodes_len, argv[flags_val[3]]);
        if (res == -1) {
            free(flags_val);
            free_nodes(&nodes, nodes_len);
            free_edges(&edges, edges_len);
            printf(MRN_ERROR);
            return EXIT_FAILURE;
        }
    }

    /* uvolni paměť */
    free(flags_val);
    free_nodes(&nodes, nodes_len);
    free_edges(&edges, edges_len);
    /*
    for (i = 0; i < nodes_len; ++i) {
        printf("-> (%f,%f) %d %s \n", nodes[i].longitude, nodes[i].latitude, nodes[i].id, nodes[i].name);
    }
    for (i = 0; i < edges_len; ++i) {
        printf("\n -> %s : %d [%d,%d] %s %d %f \n", edges[i].wkt, edges[i].id, edges[i].source, edges[i].target,
               edges[i].nation_name, edges[i].nation_id, edges[i].weight);
    }
    */

    return EXIT_SUCCESS;
}
