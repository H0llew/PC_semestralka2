#ifndef KRUSKAL_MST_H
#define KRUSKAL_MST_H

#include <stdlib.h>
#include "../graph.h"

/**
 * \struct podgraf pro union-find
 * \brief struktura reprezentuje podgraf v union-find algoritmu
 */
typedef struct subset_t {
    int parent;
    int rank;
} subset;

/**
 * Funkce hledá s kterým vrcholem je hledaný vrchol i spojen.
 * Zároveň funkce komprimuje cestu k hledanému vrcholu.
 *
 * @param subsets pole podgrafů
 * @param i prohledávaný vrchol
 * @return vrchol tvořící hranu s prohledávaným vrcholem
 */
int union_find(subset subsets[], int i);

/**
 * Funkce spojí 2 vrcholy a jejich podgrafy, pokud nějaké mají.
 *
 * @param subsets pole podgrafů
 * @param a prvý vrchol hrany
 * @param b druhý vrchol hrany
 * @return 0 pokud vše proběhlo v pořádku, jinak 1
 */
int union_union(subset subsets[], int a, int b);

/**
 * Funkce porovná 2 hrany podle jejich váhy (délky). Funkce je potřebná pro quicksort
 *
 * @param e1 první hrana
 * @param e2 druhá hrana
 * @return <ul>
 *          <li> <0 => pokud e1 < e2 </li>
 *          <li> 0 => pokud e1 = e2 </li>
 *          <li> >0 => pokud e1 > e2 </li>
 *         </ul>
 */
int compare_edges_weight(const void *e1, const void *e2);

/**
 * Funkce vytvoří minimální kostru zadaného grafu pomocí Kruskalova algoritmu
 *
 * @param g graf ve kterém hledáme minimální kostru
 * @return 0 pokud algoritmus proběhl v pořádku, jinak 1
 */
int create_mst(graph *g, node *nodes, unsigned int nodes_len, subset subsets[]);

/**
 * Provede Kruskalův algoritmus nad všemi zadanými grafy. Výsledek je zapsán do struktry grafu.
 *
 * @param graphs pole grafů
 * @param components počet grafů
 * @param nodes pole vrcholů
 * @param nodes_len délka pole vrcholů
 *
 * @return 0 pokud vše proběhlo v pořádku, jinak 1
 */
int do_msts(graph *graphs, unsigned int components, node *nodes, unsigned int nodes_len);

#endif
