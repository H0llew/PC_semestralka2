#include <stdio.h>
#include <stdlib.h>

#include "console_input.h"
#include "graph.h"
#include "nodes_io.h"
#include "edges_io.h"
#include "mst.h"
#include "mrn.h"

#define INPUT_ERROR "Input error!\n"
#define READ_ERROR "Error while reading files!n"
#define V_ERROR "Invalid vertex file.\n"
#define E_ERROR "Invalid edge file.\n"
#define MST_ERROR "Error while performing -mst!"
#define MRN_ERROR "Error while performing -mrn!"

int main(int argc, char *argv[]) {
    /* vstup z konzole */
    int *flags_val = NULL;
    unsigned int flags_len = 4;
    char *flags[] = {"-v", "-e", "-mst", "-mrn"};
    /* vrcholy a hrany */
    unsigned int read_err = 0;
    node *nodes = NULL;
    edge *edges = NULL;
    unsigned int nodes_len, edges_len;
    /* mst a mrn */
    int res;

    /* zpracuj vstup z konzole */
    flags_val = get_input_indexes(argc, argv, flags_len, flags);
    if (!flags_val) {
        printf(INPUT_ERROR);
        return EXIT_FAILURE;
    }

    /* zkontrolu zda byl zadán alespoň 1 nepovinný přepínač */
    if (flags_val[2] == 0 && flags_val[3] == 0) {
        free(flags_val);
        return EXIT_SUCCESS;
    }

    /* načti vrcholy */
    if (flags_val[0] == 0) {
        printf(V_ERROR);
        free(flags_val);
        return 1;
    } else {
        read_err = read_nodes(argv[flags_val[0]], &nodes, &nodes_len);
        if (read_err == 1) {
            free(flags_val);
            printf(V_ERROR);
            return 1;
        }
        if (read_err == 2) {
            free(flags_val);
            printf(READ_ERROR);
            return EXIT_FAILURE;
        }
    }

    /* načti hrany */
    if (flags_val[1] == 0) {
        printf(E_ERROR);
        free(flags_val);
        free_nodes(&nodes, nodes_len);
        return 2;
    } else {
        read_err = read_edges(argv[flags_val[1]], &edges, &edges_len);
        if (read_err == 1) {
            free(flags_val);
            free_nodes(&nodes, nodes_len);
            printf(E_ERROR);
            return 2;
        }
        if (read_err == 2) {
            free(flags_val);
            free_nodes(&nodes, nodes_len);
            printf(READ_ERROR);
            return EXIT_FAILURE;
        }
    }

    /* proveď mst */
    if (flags_val[2] != 0) {
        res = mst(nodes, nodes_len, edges, edges_len, argv[flags_val[2]]);
        if (res == -1) {
            free(flags_val);
            free_nodes(&nodes, nodes_len);
            free_edges(&edges, edges_len);
            printf(MST_ERROR);
            return EXIT_FAILURE;
        }
    }

    /* proveď mrn */
    if (flags_val[3] != 0) {
        res = mrn(nodes, nodes_len, argv[flags_val[3]]);
        if (res == -1) {
            free(flags_val);
            free_nodes(&nodes, nodes_len);
            free_edges(&edges, edges_len);
            printf(MRN_ERROR);
            return EXIT_FAILURE;
        }
    }

    /* uvolni paměť */
    free(flags_val);
    free_nodes(&nodes, nodes_len);
    free_edges(&edges, edges_len);

    return EXIT_SUCCESS;
}
