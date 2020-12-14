#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>

/**
 * \struct vrchol grafu
 * \brief Struktura reprezentující železniční stanice, jako hranu grafu, obsahující veškerá potřebná data pro vizualizaci.
 */
typedef struct node_t {
    unsigned int id;

    double latitude;
    double longitude;

    char *name;

    int component;
} node;

/**
 * \struct hrana grafu
 * \brief Struktura reprezentující železniční síťě, jako hranu grafu, obsahující veškerá potřebná data pro vizualizaci.
 */
typedef struct edge_t {
    unsigned int id;

    unsigned int source;
    unsigned int target;

    char *wkt;
    char *nation_name;
    unsigned int nation_id;

    int component;

    double weight;
} edge;

/**
 * \struct graf
 * \brief Struktura reprezentující graf pomocí jeho hran.
 * Forma odpovídá potřebě pro Kruskalův algoritmus hledání minimální kostry grafu.
 */
typedef struct graph_t {
    unsigned int v, e;

    edge *edges;
    edge *mst;
} graph;

/* testovací fce */

int get_node_pos(unsigned int n, node *nodes, unsigned int nodes_len);

node create_node(unsigned int id, double latitude, double longitude);

edge create_edge(unsigned int id, unsigned int source, unsigned int target, double weight);

graph *create_graphs(node *nodes, unsigned int nodes_len,
                     edge *edges, unsigned int edges_len,
                     unsigned int components);

#endif
