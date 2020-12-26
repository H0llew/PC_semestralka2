#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>

/**
 * \struct vrchol grafu
 * \brief Struktura reprezentuje železniční stanice, jako hranu grafu.
 *        Struktura obsahuje veškerá potřebná data pro vizualizaci.
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
 * \brief Struktura reprezentuje železniční síť, jako hranu grafu.
 *        Struktura obsahuje veškerá potřebná data pro vizualizaci.
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
 * Vrátí pozici vrcholu v zadaném poli vrcholů
 *
 * @param n identifikátor hledaného vrcholu
 * @param nodes pole vrcholů
 * @param nodes_len délka pole vrcholů
 *
 * @return pozice vrcholu
 */
int get_node_pos(unsigned int n, node *nodes, unsigned int nodes_len);

/**
 * Uvolní paměť vrcholu
 *
 * @param node vrchol
 */
void free_node(node *node);

/**
 * Uvolní paměť pole vrcholů
 *
 * @param nodes pole vrcholů
 * @param nodes_len délka pole vrcholů
 */
void free_nodes(node **nodes, unsigned int nodes_len);

/**
 * Uvolní paměť hrany
 *
 * @param edge hrany
 */
void free_edge(edge *edge);

/**
 * Uvolní paměť pole hran
 *
 * @param edges pole hran
 * @param edges_len délka pole hran
 */
void free_edges(edge **edges, unsigned int edges_len);

#endif
