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

graph *create_graphs(node *nodes, unsigned int nodes_len,
                     edge *edges, unsigned int edges_len,
                     unsigned int components) {

    graph *gs = NULL, *g = NULL;
    unsigned int *nodes_in_component_count = NULL;
    unsigned int *vertex_in_component_count = NULL;
    unsigned int i, j, d;
    int comp;

    /* kontrola vstupu */
    if (!nodes || nodes_len == 0 || !edges || edges_len == 0 || components == 0)
        return NULL;

    gs = malloc(sizeof(graph) * components);
    if (!gs)
        return NULL;

    nodes_in_component_count = malloc(sizeof(unsigned int) * components);
    if (!nodes_in_component_count) {
        free(gs);
        return NULL;
    }

    vertex_in_component_count = malloc(sizeof(unsigned int) * components);
    if (!vertex_in_component_count) {
        free(gs);
        free(nodes_in_component_count);
        return NULL;
    }

    for (i = 0; i < components; ++i) {
        nodes_in_component_count[i] = 0;
        vertex_in_component_count[i] = 0;
    }

    for (i = 0; i < nodes_len; ++i) {
        comp = nodes[i].component;
        if (comp > (int) components) {
            continue;
        }
        nodes_in_component_count[comp]++;
    }

    for (i = 0; i < edges_len; ++i) {
        comp = edges[i].component;
        if (comp > (int) components) {
            continue;
        }
        vertex_in_component_count[comp]++;
    }

    for (i = 0; i < components; ++i) {
        g = malloc(sizeof(graph));
        if (!g)
            return NULL;

        g->e = vertex_in_component_count[i];
        g->v = nodes_in_component_count[i];

        g->edges = malloc(sizeof(edge) * g->e);
        /*
        for (j = 0; j < g->e; ++j) {
            for (d = 0; d < edges_len; ++d) {
                if (edges[d].component == (int) i) {
                    g->edges[j] = edges[d];
                }
            }
        }
        */
        d = 0;
        for (j = 0; j < edges_len; j++) {
            if (edges[j].component == (int) i) {
                g->edges[d] = edges[j];
                d++;
            }

            if (d == g->e)
                break;
        }

        *(gs + i) = *g;
        free(g);
    }

    return gs;
}

