#include "graph.h"

int get_node_pos(unsigned int n, node *nodes, unsigned int nodes_len) {
    unsigned int assumed_pos;
    int i = 0;

    /* kontrola parametrů */
    if (!nodes || nodes_len == 0)
        return -1;

    if (n > nodes_len)
        assumed_pos = (nodes_len - 1);
    else
        assumed_pos = (n - 1);

    for (i = (int) assumed_pos; i >= 0; --i) {
        if (nodes[i].id == n)
            return (int) i;
    }

    return -1;
}

/* uvolňování pameťi */

void free_nodes(node **nodes, unsigned int nodes_len) {
    unsigned int i;

    /* kontrola parametrů*/
    if (!nodes || !(*nodes))
        return;

    for (i = 0; i < nodes_len; ++i) {
        /* free((*nodes + i)->name); */
        free_node((*nodes + i));
    }
    free(*nodes);
    *nodes = NULL;
}

void free_node(node *node) {
    if (!node)
        return;

    free(node->name);
}

void free_edges(edge **edges, unsigned int edges_len) {
    unsigned int i;

    if (!edges || !(*edges))
        return;

    for (i = 0; i < edges_len; ++i) {
        free_edge(*edges + i);
    }
    free(*edges);
    *edges = NULL;
}

void free_edge(edge *edge) {
    if (!edge)
        return;

    free(edge->wkt);
    free(edge->nation_name);
}
