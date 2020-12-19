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

    graph *gs = NULL;
    unsigned int *nodes_in_component_count = NULL;
    unsigned int *vertex_in_component_count = NULL;
    unsigned int i, j, d;
    int comp;

    /* kontrola parametrů */
    if (!nodes || nodes_len == 0 || !edges || edges_len == 0 || components == 0)
        return NULL;

    /* mem */
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

    /* vynuluj mi pole počtů vrcholů a hran */
    for (i = 0; i < components; ++i) {
        nodes_in_component_count[i] = 0;
        vertex_in_component_count[i] = 0;
    }

    /* přiřaď mi ke každé komponentě počet jejich vrcholů */
    for (i = 0; i < nodes_len; ++i) {
        comp = nodes[i].component;
        if (comp > (int) components || comp < 0) {
            /* špatné ignorujeme */
            continue;
        }
        nodes_in_component_count[comp]++;
    }

    /* přiřaď mi ke každé komponentě počet jejich hran */
    for (i = 0; i < edges_len; ++i) {
        comp = edges[i].component;
        if (comp > (int) components || comp < 0) {
            /* špatné ignorujeme */
            continue;
        }
        vertex_in_component_count[comp]++;
    }

    for (i = 0; i < components; ++i) {
        /*
        g = malloc(sizeof(graph));
        if (!g) {
            return NULL;
        }
        */

        gs[i].mst = NULL;
        gs[i].e = vertex_in_component_count[i];
        gs[i].v = nodes_in_component_count[i];

        gs[i].edges = malloc(sizeof(edge) * gs[i].e);
        if (!gs[i].edges) {
            for (j = i - 1; j >= 0; ++j) {
                free(gs[j].edges);
            }
            free(gs);
            free(nodes_in_component_count);
            free(vertex_in_component_count);
            return NULL;
        }
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
                gs[i].edges[d] = edges[j];
                d++;
            }

            if (d == gs[i].e)
                break;
        }
        /* free(g); */
    }

    free(nodes_in_component_count);
    free(vertex_in_component_count);

    return gs;
}

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
