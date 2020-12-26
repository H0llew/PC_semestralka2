#include "mst.h"
#include "edges_io.h"

int mst(node *nodes, unsigned int nodes_len, edge *edges, unsigned int edges_len, char *output_file) {
    int res;
    /* mst */
    edge *mst = NULL;
    unsigned int mst_len = 0;

    /* kontrola vstupu */
    if (!nodes || nodes_len == 0 || !edges || edges_len == 0 || !output_file)
        return -1;

    /* proveď Kruskalův algoritmus, pro zjištení mst */
    res = create_mst(nodes, nodes_len, edges, edges_len, &mst, &mst_len);
    if (res == -1 || !mst || mst_len == 0)
        return -1;

    /* seřaď hrany sestupně podle id */
    qsort(mst, mst_len, sizeof(edge), compare_edges_id);

    /* zapiš výsledek do souboru */
    res = create_edges_file(output_file, mst, mst_len);
    if (res == -1) {
        /* uvolni paměť */
        free(mst);
        return -1;
    }

    /* uvolni paměť */
    free(mst);
    return 0;
}

int compare_edges_id(const void *e1, const void *e2) {

    double e1_w, e2_w;

    e1_w = ((edge *) e1)->id;
    e2_w = ((edge *) e2)->id;

    if (e1_w > e2_w)
        return -1;
    else if (e1_w < e2_w)
        return 1;
    else
        return 0;
}
