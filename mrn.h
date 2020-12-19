#ifndef MRN_H
#define MRN_H

#include <math.h>
#include <stdlib.h>
#include "graph.h"
#include "kruskal_mst.h"
#include "edges_io.h"

/**
 * Ze zadaných vrcholů vytvoří minimální kostru propojující všechny zadané vrcholy
 *
 * @param nodes pole vrcholů
 * @param nodes_len délka pole vrcholů
 * @param file_name název souboru
 *
 * @return 0 pokud vše proběhlo v pořádku, jinak NULL
 */
int mrn(node *nodes, unsigned int nodes_len, char *file_name);

/**
 * Vytvoří úplný graf ze zadaných vrcholů
 *
 * @param nodes pole vrcholů
 * @param nodes_len délka pole vrcholů
 *
 * @return graf nebo NULL
 */
graph *create_complete_graph(node *nodes, unsigned int nodes_len);

/**
 * Vypočítá vzdálenost dvou bodů na Zemi
 *
 * @param longitude_a zeměpisná délka prvního bodu
 * @param latitude_a zeměpisná šířka prvního bodu
 * @param longitude_b zeměpisná délka druhého bodu
 * @param latitude_b zeměpisná šířka druhého bodu
 *
 * @return vzdálenost dvou bodů na Zemi
 */
double get_distance(double longitude_a, double latitude_a, double longitude_b, double latitude_b);

/**
 * Převodník stupňů na radiány
 *
 * @param x stupeň
 *
 * @return zadaný stupeň v radiánech
 */
double degrees_to_radians(double x);

/**
 * Doplní všem hranám data potřebná k vizualizaci
 *
 * @param edges pole hran
 * @param edges_len délka pole hran
 * @param nodes pole vrcholů
 * @param nodes_len délka pole vrcholů
 *
 * @return 0 pokud se vše podařilo, jinak -1
 */
int attach_edges_info(edge *edges, unsigned int edges_len, node *nodes, unsigned int nodes_len);

/**
 * Obrátí pole hran
 *
 * @param edges pole hran
 * @param edges_len délka pole hran
 */
void reverse_edges(edge **edges, unsigned int edges_len);

#endif
