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

/**
 * Vrátí pozici vrcholu v poli vrcholů
 *
 * @param n vrchol
 * @param nodes pole vrchoů
 * @param nodes_len délka pole vrcholů
 *
 * @return pozice vrcholu
 */
int get_node_pos(unsigned int n, node *nodes, unsigned int nodes_len);

/**
 * Vytvoří grafy z pole hran a vrcholů, pro zadaný počet komponent
 *
 * @param nodes pole vrcholů
 * @param nodes_len délka pole vrcholů
 * @param edges hrany
 * @param edges_len délka pole hran
 * @param components počet komponent
 *
 * @return pole grafů
 */
graph *create_graphs(node *nodes, unsigned int nodes_len,
                     edge *edges, unsigned int edges_len,
                     unsigned int components);

void free_node(node *node);

void free_nodes(node **nodes, unsigned int nodes_len);

void free_edge(edge *edge);

void free_edges(edge **edges, unsigned int edges_len);

#endif
