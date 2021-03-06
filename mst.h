#ifndef MST_H
#define MST_H

#include "graph.h"
#include "kruskal_mst.h"

/**
 * Vykoná a vypíše hrany minimální kostru/kostry zadaného grafu pomocí jeho hran a vrcholů
 *
 * @param nodes pole vrcholů
 * @param nodes_len délka pole vrcholů
 * @param edges pole hran
 * @param edges_len délka pole hran
 * @param output_file
 *
 * @return 0 pokud vše proběhlo v pořádku, jinak -1
 */
int mst(node *nodes, unsigned int nodes_len, edge *edges, unsigned int edges_len, char *output_file);

/**
 * Porovnávací metoda -> porovná hrany podle jejich id
 *
 * @param e1 hrana 1
 * @param e2 hrana 2
 *
 * @return sestupné řazení
 */
int compare_edges_id(const void *e1, const void *e2);

#endif
