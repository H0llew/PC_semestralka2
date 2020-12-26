#ifndef KRUSKAL_MST_H
#define KRUSKAL_MST_H

#include <stdlib.h>
#include "graph.h"

/**
 * \struct podgraf pro union-find
 * \brief struktura reprezentuje podgraf v union-find algoritmu
 */
typedef struct subset_t {
    int parent;
    int rank;
} subset;

/**
 * Funkce hledá s kterým vrcholem je hledaný vrchol propojen.
 *
 * @param subsets pole podgrafů
 * @param i prohledávaný vrchol
 * @return vrchol tvořící hranu s prohledávaným vrcholem nebo -1
 */
int union_find(subset subsets[], int i);

/**
 * Funkce spojí 2 vrcholy a jejich podgrafy, pokud nějaké mají.
 *
 * @param subsets pole podgrafů
 * @param a prvý vrchol hrany
 * @param b druhý vrchol hrany
 * @return 0 pokud vše proběhlo v pořádku, jinak -1
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
 * Funkce vytvoří a vrátí hrany minimální kostru grafu, nebo komponent grafu, pokud je zadán graf s více komponentami.
 *
 * @param nodes pole vrcholů
 * @param nodes_len délka pole vrcholů
 * @param edges pole hran
 * @param edges_len délka pole hran
 * @param mst vyhledané hrany minimální kostry/koster
 * @param mst_len počet hran v minimální kostře/koster
 *
 * @return 0 pokud funkce proběhla v pořádku, jinak -1
 */
int create_mst(node *nodes, unsigned int nodes_len, edge *edges, unsigned int edges_len,
               edge **mst, unsigned int *mst_len);

#endif
