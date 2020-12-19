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
        return -1;

    /* najdi kořen "a" a "b" tj. hrany [a;b]*/
    x_root = union_find(subsets, a);
    y_root = union_find(subsets, b);
    if (x_root < 0 || y_root < 0)
        return -1;

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
    int a, b, res;

    /* kontrola parametrů */
    if (!g || !g->edges || !nodes || nodes_len == 0 || !subsets)
        return -1;

    if (g->e == 0 || g->v <= 1)
        return 0;

    /* 1. krok algoritmu -> seřaď prvky podle váhy(délky tratě) vzestupně */
    qsort(g->edges, g->e, sizeof(edge), compare_edges_weight);

    /* 2. a 3. krok algoritmu -> hledej a přiřazuj nejlevnější váhy(délky tratě) a kontroluj cykly*/
    g->mst = malloc(sizeof(edge) * (g->v - 1));
    if (!g->mst)
        return -1;

    /* opakuj 2. a 3. krok algoritmu*/
    e = 0;
    i = 0;
    while (e < (g->v - 1) && i < (g->e)) {
        /* curr = g->edges[i]; */
        a = union_find(subsets, get_node_pos(g->edges[i].source, nodes, nodes_len));
        b = union_find(subsets, get_node_pos(g->edges[i].target, nodes, nodes_len));
        if (a == -1 || b == -1) {
            /* protože shallow copy stačí */
            free(g->mst);
            g->mst = NULL;
            return -1;
        }

        if (a != b) {
            g->mst[e] = g->edges[i];
            res = union_union(subsets, a, b);
            if (res == -1) {
                /* protože shallow copy stačí */
                free(g->mst);
                g->mst = NULL;
                return -1;
            }
            e++;
        }

        i++;
    }
    /* g->mst = mst; */
    return 0;
}

int do_msts(graph *graphs, unsigned int components, node *nodes, unsigned int nodes_len) {
    unsigned int i;
    int res;
    subset *subsets = NULL;

    /* kontrola parametrů */
    if (!graphs || components == 0 || !nodes || nodes_len == 0)
        return -1;

    /* vytvoř subset */
    subsets = malloc(sizeof(subset) * nodes_len);
    for (i = 0; i < nodes_len; ++i) {
        subsets[i].parent = (int) i;
        subsets[i].rank = 0;
    }

    for (i = 0; i < components; ++i) {
        /* projdi všechny komponenty grafu */
        res = create_mst(&graphs[i], nodes, nodes_len, subsets);
        if (res == -1) {
            free(subsets);
            return -1;
        }
    }

    free(subsets);
    return 0;
}
