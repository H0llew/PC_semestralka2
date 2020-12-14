#include "kruskal_mst.h"

int union_find(subset subsets[], int i) {
    if (!subsets || i < 0)
        return -1;

    if (subsets[i].parent != i) {
        /* hledej a komprimuj cestu */
        subsets[i].parent = union_find(subsets, subsets[i].parent);
    }

    return subsets[i].parent;
}

int union_union(subset subsets[], int a, int b) {
    int x_root, y_root;

    /* zkontroluj parametry */
    if (!subsets || a < 0 || b < 0)
        return 1;

    /* najdi kořen "a" a "b" tj. hrany [a;b]*/
    x_root = union_find(subsets, a);
    y_root = union_find(subsets, b);
    if (x_root < 0 || y_root < 0)
        return 1;

    /* proveď přiřazení a zarovnání */
    if (subsets[x_root].rank < subsets[y_root].rank)
        subsets[x_root].parent = y_root;
    else if (subsets[x_root].rank > subsets[y_root].rank)
        subsets[y_root].parent = x_root;
    else {
        /* když jsou stejné, tak jedno kdo bude rodičem */
        subsets[y_root].parent = x_root;
        subsets[x_root].rank++;
    }

    return 0;
}

int compare_edges_weight(const void *e1, const void *e2) {

    double e1_w, e2_w;

    e1_w = ((edge *) e1)->weight;
    e2_w = ((edge *) e2)->weight;

    if (e1_w < e2_w)
        return -1;
    else if (e1_w > e2_w)
        return 1;
    else
        return 0;
}

int create_mst(graph *g, node *nodes, unsigned int nodes_len, subset subsets[]) {
    unsigned int e, i;
    int a, b;
    /* subset *subsets = NULL; */
    edge *mst = NULL;

    /* ověření parametrů */
    if (!g || !g->edges || g->e == 0 || g->v == 0)
        return 1;

    /* nemá cenu řešit mst */
    if (g->e == 0 || g->v == 1)
        return 2;

    /* 1. krok algoritmu -> seřaď prvky podle váhy(délky tratě) vzestupně */
    qsort(g->edges, g->e, sizeof(edge), compare_edges_weight);

    /* 2. a 3. krok algoritmu -> hledej a přiřazuj nejlevnější váhy(délky tratě) a kontroluj cykly*/

    /*
    / alokuj paměť pro mst /
    subsets = malloc(sizeof(subset) * g->v);
    if (!subsets)
        return 3;
    / počáteční stav subsetu /
    for (i = 0; i < g->v; ++i) {
        subsets[i].parent = (int) i;
        subsets[i].rank = 0;
    }
    */

    mst = malloc(sizeof(edge) * (g->v - 1));
    if (!mst)
        return 3;

    /* opakuj 2. a 3. krok algoritmu*/
    e = 0;
    i = 0;
    while (e < (g->v - 1) && i < (g->e)) {

        edge curr = g->edges[i];

        /* zkontroluj cyklus a popřípadě přiřad hranu do mst */
        /* TODO potenciální problémek :D co když hrana neexistuje? */
        /* a = union_find(subsets, (int) (curr.source - 1)); */
        /* b = union_find(subsets, (int) (curr.target - 1)); */
        a = union_find(subsets, get_node_pos(curr.source, nodes, nodes_len));
        b = union_find(subsets, get_node_pos(curr.target, nodes, nodes_len));

        if (a != b) {
            mst[e] = curr;
            union_union(subsets, a, b);
            e++;
        }

        i++;
    }

    g->mst = mst;

    return 0;
}

int do_msts(graph *graphs, unsigned int components, node *nodes, unsigned int nodes_len) {
    unsigned int i;
    subset *subsets = NULL;

    /* unpolished */

    /* vytvoř subset */
    subsets = malloc(sizeof(subset) * nodes_len);
    for (i = 0; i < nodes_len; ++i) {
        subsets[i].parent = (int) i;
        subsets[i].rank = 0;
    }

    for (i = 0; i < components; ++i) {
        /* projdi všechny komponenty grafu */
        create_mst(&graphs[i], nodes, nodes_len, subsets);
    }

    return 0;
}
