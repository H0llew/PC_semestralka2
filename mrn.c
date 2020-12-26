#include "mrn.h"

#define PI 3.14159265358979323846
/* v metrech */
#define EARTH_RADIUS 6371110

int mrn(node *nodes, unsigned int nodes_len, char *file_name) {
    unsigned int i;
    int res = 0;

    edge *all_edges = NULL; /* bude jich (n-1)/2 */
    edge *mst = NULL;
    unsigned int mst_len = 0; /* možná zbytečné, protože víme že jich bude n-1 (máme jen 1 komponentu)*/

    /* kontrola parametrů */
    if (!nodes || nodes_len <= 1 || !file_name)
        return -1;

    all_edges = create_complete_graph(nodes, nodes_len);
    if (!all_edges)
        return -1;

    res = create_mst(nodes, nodes_len, all_edges, (nodes_len - 1) / 2, &mst, &mst_len);
    if (res == -1) {
        free(all_edges);
        return -1;
    }

    reverse_edges(&mst, mst_len); /* protože sestupné pořadí je vyžadováno */
    res = attach_edges_info(mst, mst_len, nodes, nodes_len);
    if (res == -1) {
        free(all_edges);
        free(mst);
        return -1;
    }

    res = create_edges_file(file_name, mst, mst_len);
    if (res == -1) {
        free_edges(&mst, mst_len); /* je potžeba uvolnovat i prvky hrany -> není shallow copy */
        free(all_edges);
        return -1;
    }

    free_edges(&mst, mst_len);
    free(all_edges);

    return 0;
}

edge *create_complete_graph(node *nodes, unsigned int nodes_len) {
    unsigned int i, j, edges_len, curr_edge;
    edge *all_edges = NULL;

    /* kontrola parametrů*/
    if (!nodes || nodes_len == 0)
        return NULL;

    /* vypočti kolik bude hran */
    edges_len = (nodes_len * (nodes_len - 1)) / 2;
    all_edges = malloc(sizeof(edge) * edges_len);
    if (!all_edges)
        return NULL;

    /* udělej hrany mezi všemi vrcholy v*/
    curr_edge = 0;
    for (i = 0; i < nodes_len; ++i) {
        for (j = i + 1; j < nodes_len; ++j) {
            (all_edges + curr_edge)->source = nodes[i].id;
            (all_edges + curr_edge)->target = nodes[j].id;
            (all_edges + curr_edge)->weight = get_distance(nodes[i].longitude, nodes[i].latitude,
                                                           nodes[j].longitude, nodes[j].latitude);
            (all_edges + curr_edge)->id = 0;
            (all_edges + curr_edge)->component = 0;
            (all_edges + curr_edge)->nation_id = 0;
            (all_edges + curr_edge)->nation_name = NULL;
            (all_edges + curr_edge)->wkt = NULL;

            curr_edge++;
        }
    }

    return all_edges;
}

double get_distance(double longitude_a, double latitude_a, double longitude_b, double latitude_b) {
    double res = 0;

    longitude_a = degrees_to_radians(longitude_a);
    longitude_b = degrees_to_radians(longitude_b);
    latitude_a = degrees_to_radians(90 - latitude_a);
    latitude_b = degrees_to_radians(90 - latitude_b);

    res = acos((cos(latitude_b) * cos(latitude_a)) +
               (sin(latitude_b) * sin(latitude_a) * cos(longitude_b - longitude_a)));

    res = res * EARTH_RADIUS;

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
    edge *reverse_uno_card = NULL;
    int i, curr;

    if (!edges || !(*edges) || edges_len == 0)
        return;

    reverse_uno_card = malloc(sizeof(edge) * edges_len);
    if (!reverse_uno_card)
        return;

    curr = 0;
    for (i = (int) (edges_len - 1); i >= 0; --i) {
        reverse_uno_card[curr] = (*edges)[i];
        curr++;
    }

    free(*edges);
    *edges = reverse_uno_card;
}
