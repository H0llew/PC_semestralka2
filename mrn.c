#include "mrn.h"

#define PI 3.14159265358979323846

int mrn(node *nodes, unsigned int nodes_len, char *file_name) {
    unsigned int i;
    graph *g = NULL;
    int res = 0;

    /* kontrola parametrů */
    if (!nodes || nodes_len <= 1 || !file_name)
        return -1;

    g = create_complete_graph(nodes, nodes_len);
    if (!g)
        return -1;

    res = do_msts(g, 1, nodes, nodes_len);
    if (res == -1) {
        free_graphs(&g, 1);
        return -1;
    }

    reverse_edges(&g->mst, nodes_len - 1);
    res = attach_edges_info(g->mst, nodes_len - 1, nodes, nodes_len);
    if (res == -1) {
        free_graphs(&g, 1);
        return -1;
    }

    res = create_edges_file(file_name, g->mst, nodes_len - 1);
    if (res == -1) {
        free_graphs(&g, 1);
        return -1;
    }

    for (i = 0; i < nodes_len - 1; ++i) {
        free((g->mst + i)->wkt);
        free((g->mst + i)->nation_name);
    }
    free(g->edges);
    free(g->mst);
    free(g);

    return 0;
}

graph *create_complete_graph(node *nodes, unsigned int nodes_len) {
    unsigned int i, j, edges_len, curr_edge;
    graph *g = NULL;

    /* kontrola parametrů*/
    if (!nodes || nodes_len == 0)
        return NULL;

    g = malloc(sizeof(graph));
    if (!g)
        return NULL;

    /* vypočti kolik bude hran */
    edges_len = (nodes_len * (nodes_len - 1)) / 2;
    g->edges = malloc(sizeof(edge) * edges_len);
    if (!g->edges) {
        free(g);
        return NULL;
    }

    /* udělej hrany mezi všemi vrcholy v*/
    curr_edge = 0;
    for (i = 0; i < nodes_len; ++i) {
        for (j = i + 1; j < nodes_len; ++j) {

            /*
            curr = malloc(sizeof(edge));
            if (!curr) {
                return NULL;
            }
            */
            /*
            curr->source = nodes[i].id;
            curr->target = nodes[j].id;
            curr->weight = get_distance(nodes[i].longitude, nodes[i].latitude, nodes[j].longitude, nodes[j].latitude);

            g->edges[curr_edge] = *curr;
            free(curr);
            */

            (g->edges + curr_edge)->source = nodes[i].id;
            (g->edges + curr_edge)->target = nodes[j].id;
            (g->edges + curr_edge)->weight = get_distance(nodes[i].longitude, nodes[i].latitude,
                                                          nodes[j].longitude, nodes[j].latitude);
            (g->edges + curr_edge)->id = 0;
            (g->edges + curr_edge)->component = 0;
            (g->edges + curr_edge)->nation_id = 0;
            (g->edges + curr_edge)->nation_name = NULL;
            (g->edges + curr_edge)->wkt = NULL;

            curr_edge++;
        }
    }

    g->e = edges_len;
    g->v = nodes_len;

    return g;
}

double get_distance(double longitude_a, double latitude_a, double longitude_b, double latitude_b) {
    double res = 0;

    longitude_a = degrees_to_radians(longitude_a);
    longitude_b = degrees_to_radians(longitude_b);
    latitude_a = degrees_to_radians(90 - latitude_a);
    latitude_b = degrees_to_radians(90 - latitude_b);

    res = acos((cos(latitude_b) * cos(latitude_a)) +
               (sin(latitude_b) * sin(latitude_a) * cos(longitude_b - longitude_a)));

    res = res * 6371110;

    return res;
}

double degrees_to_radians(double x) {
    return x * (PI / 180);
}

int attach_edges_info(edge *edges, unsigned int edges_len, node *nodes, unsigned int nodes_len) {
    unsigned int i, j;
    char *buffer = NULL;
    node *s, *t;
    int pos_s, pos_t;

    /* kontrola parametrů */
    if (!edges || edges_len == 0 || !nodes || nodes_len == 0)
        return -1;

    for (i = 0; i < edges_len; ++i) {
        buffer = malloc(sizeof(char) * MAX_REST_LENGTH);
        if (!buffer)
            return -1;

        pos_s = get_node_pos(edges[i].source, nodes, nodes_len);
        pos_t = get_node_pos(edges[i].target, nodes, nodes_len);
        if (pos_s == -1 || pos_t == -1) {
            for (j = 0; j < i - 1; ++j) {
                free((edges + j)->wkt);
                free((edges + j)->nation_name);
            }
            free(buffer);
            return -1;
        }

        s = &nodes[pos_s];
        t = &nodes[pos_t];

        sprintf(buffer, "\"MULTILINESTRING ((%f %f,%f %f))\"", s->longitude, s->latitude, t->longitude, t->latitude);
        edges[i].id = i + 1;
        edges[i].nation_id = 0; /* neznám */

        edges[i].nation_name = malloc(sizeof(char) + 1);
        if (!edges[i].nation_name) {
            for (j = 0; j < i - 1; ++j) {
                free((edges + j)->wkt);
                free((edges + j)->nation_name);
            }
            free(buffer);
            return -1;
        }
        strcpy(edges[i].nation_name, ""); /* neznám */

        edges[i].wkt = malloc(sizeof(char) * (strlen(buffer) + 1));
        if (!edges[i].wkt) {
            free((edges + i)->nation_name);
            for (j = 0; j < i - 1; ++j) {
                free((edges + j)->wkt);
                free((edges + j)->nation_name);
            }
            free(buffer);
            return -1;
        }
        strcpy(edges[i].wkt, buffer);

        free(buffer);
    }

    return 0;
}

void reverse_edges(edge **edges, unsigned int edges_len) {
    edge *uno_card = NULL;
    int i, curr;

    if (!edges || !(*edges) || edges_len == 0)
        return;

    uno_card = malloc(sizeof(edge) * edges_len);
    if (!uno_card)
        return;

    curr = 0;
    for (i = (int) (edges_len - 1); i >= 0; --i) {
        uno_card[curr] = (*edges)[i];
        curr++;
    }

    free(*edges);
    *edges = uno_card;
}
