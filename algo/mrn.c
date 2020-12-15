#include "mrn.h"

#define PI 3.14159265358979323846

int mrn(char *file_name, node *nodes, unsigned int nodes_len) {
    graph *g = NULL;
    int res = 0;

    /* kontrola parametrů */
    if (!nodes || nodes_len == 0 || !file_name)
        return -1;

    g = create_complete_graph(nodes, nodes_len);
    if (!g)
        return -1;

    res = do_msts(g, 1, nodes, nodes_len);
    if (res == -1)
        return -1;

    res = attach_edges_info(g->mst, nodes_len - 1, nodes, nodes_len);
    if (res == -1)
        return -1;

    res = create_edges_file(file_name, g->mst, nodes_len - 1);
    if (res == -1)
        return -1;

    free(g->edges);
    free(g->mst);
    free(g);

    return 0;
}

graph *create_complete_graph(node *nodes, unsigned int nodes_len) {
    unsigned int i, j, edges_len, curr_edge;
    edge *curr = NULL;
    graph *g;

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

            curr = malloc(sizeof(edge));
            if (!curr) {
                return NULL;
            }

            curr->source = nodes[i].id;
            curr->target = nodes[j].id;
            curr->weight = get_distance(nodes[i].longitude, nodes[i].latitude, nodes[j].longitude, nodes[j].latitude);

            g->edges[curr_edge] = *curr;
            free(curr);

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

    res = res * 6371.11;

    return res;
}

double degrees_to_radians(double x) {
    return x * (PI / 180);
}

int attach_edges_info(edge *edges, unsigned int edges_len, node *nodes, unsigned int nodes_len) {
    unsigned int i;
    char *buffer = NULL;
    node *s, *t;

    /* kontrola parametrů */
    if (!edges || edges_len == 0 || !nodes || nodes_len == 0)
        return -1;

    for (i = 0; i < edges_len; ++i) {
        buffer = malloc(sizeof(char) * MAX_REST_LENGTH);
        if (!buffer)
            return -1;

        s = &nodes[get_node_pos(edges[i].source, nodes, nodes_len)];
        t = &nodes[get_node_pos(edges[i].target, nodes, nodes_len)];

        sprintf(buffer, "\"MULTILINESTRING ((%f %f,%f %f))\"", s->longitude, s->latitude, t->longitude, t->latitude);
        edges[i].id = i + 1;
        edges[i].nation_id = 0;

        edges[i].nation_name = malloc(sizeof(char) + 1);
        if (!edges[i].nation_name)
            return -1;
        strcpy(edges[i].nation_name, "");

        edges[i].wkt = malloc(sizeof(char) * (strlen(buffer) + 1));
        if (!edges[i].wkt)
            return -1;
        strcpy(edges[i].wkt, buffer);

        free(buffer);
    }

    return 0;
}
