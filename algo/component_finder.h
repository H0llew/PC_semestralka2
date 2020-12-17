#ifndef COMPONENT_FINDER_H
#define COMPONENT_FINDER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../graph.h"

/**
 * Funkce zjistí všechny sousedy zadaného vrcholu, tak že projde všechny zadané hrany grafu.
 *
 * @param n vrchol u kterého hledáme sousedy
 * @param edges hrany
 * @param edges_len délka hran
 * @param neighbours ukazatel na pole, kam budou zapsáni sousedi
 * @param neighbours_len ukazatel na délku pole sousedů
 * @param component aktuální komponenta, ve které se nachází prohledávaný vrchol
 */
void find_neighbours(unsigned int n,
                     edge *edges, unsigned int edges_len,
                     node *nodes, unsigned int nodes_len,
                     unsigned int **neighbours, unsigned int *neighbours_len,
                     int component);

/**
 * Funkce provede DFS nad zadaným vrcholem. DFS je modifikováno,
 * tak že při pruchodu přiřazuje hranám id komponenty ve které se nachází
 *
 * @param n procházený vrchol
 * @param mark pole stavů vrcholů
 * @param edges hrany
 * @param edges_len délka pole hran
 * @param nodes vrcholy
 * @param nodes_len délka pole vrcholů
 * @param component aktuální komponenta, ve které se nachází zadaný vrchol
 */
void dfs(unsigned int n, unsigned int *mark,
         edge *edges, unsigned int edges_len,
         node *nodes, unsigned int nodes_len,
         int component);

/**
 * Nalezne všem vrcholům a hranám jejich komponentu ve které se nacházejí
 *
 * @param nodes pole vrcholů
 * @param nodes_len délka pole vrcholů
 * @param edges pole hran
 * @param edges_len délka pole hran
 *
 * @return
 */
int find_components(node *nodes, unsigned int nodes_len, edge *edges, unsigned int edges_len);

#endif
