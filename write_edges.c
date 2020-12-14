#include "write_edges.h"

int create_edges_file(char *file_name, edge *edges, unsigned int edges_len) {
    FILE *file = NULL;
    unsigned int i;
    char *buffer = NULL;

    /* kontrola vstupu */
    file = fopen(file_name, "w");
    if (!file)
        return -1;

    /* zapisování do souboru */
    fputs(FILE_HEADER_EDGES_1, file);
    for (i = 0; i < edges_len; ++i) {
        buffer = malloc(sizeof(char) * MAX_SZ_EDGE_LENGTH);
        if (!buffer)
            return -1;

        sprintf(buffer, "%s,%d,%u,%s,%d,%d,%f,,,,,,,,,,,,,,,,,,\n", edges[i].wkt, edges[i].id, edges[i].nation_id,
                edges[i].nation_name, edges[i].source, edges[i].target, edges[i].weight);

        fputs(buffer, file);

        free(buffer);
    }


    fclose(file);

    return 0;
}

