#include "mst.h"
#include "../edges_io.h"

int mst(node *nodes, unsigned int nodes_len, edge *edges, unsigned int edges_len, char *output_file) {
    int components = 0, res;
    graph *graphs = NULL;
    /* join */
    unsigned int union_edges_len = 0, i;
    edge *union_edges = NULL;

    /* kontrola vstupu */
    if (!nodes || nodes_len == 0 || !edges || edges_len == 0 || !output_file)
        return -1;

    /* přiřaď hranám a vrcholům číslo komponenty, ve které se nachází */
    components = find_components(nodes, nodes_len, edges, edges_len);
    if (components == -1)
        return -1;

    /* vytvoř komponenty grafu */
    graphs = create_graphs(nodes, nodes_len, edges, edges_len, components);
    if (graphs == NULL)
        return -1;

    /* proveď Kruskalův algoritmus pro každou komponentu */
    res = do_msts(graphs, components, nodes, nodes_len);
    if (res == -1)
        return -1;

    /* propoj všechny hrany ve všech komponentách a seřaď je */
    res = join_edges(graphs, components, &union_edges, &union_edges_len);
    if (res == -1)
        return -1;

    qsort(union_edges, union_edges_len, sizeof(edge), compare_edges_id);

    for (i = 0; i < union_edges_len; ++i) {
        printf("%d", union_edges[i].id);
    }

    /* zapiš výsledek do souboru */
    create_edges_file(output_file, union_edges, union_edges_len);

    return 0;
}

int join_edges(graph *graphs, unsigned int components, edge **edges, unsigned int *edges_len) {
    unsigned int count, i, j, k;

    /* kontrola vstupu */
    if (!graphs || !graphs->mst || graphs->v == 0 || graphs->e == 0 || components == 0 || !edges || !edges_len)
        return -1;

    /* zjisti kolik hran je celkem ze všech mst */
    count = 0;
    for (i = 0; i < components; ++i) {
        count += (graphs[i].v - 1);
    }

    *edges = malloc(sizeof(edge) * count);
    if (!(*edges))
        return -1;

    /* přidej hrany do výstupu */
    k = 0;
    for (i = 0; i < components; ++i) {
        for (j = 0; j < (graphs[i].v - 1); ++j) {
            (*edges)[k] = graphs[i].edges[j];
            k++;
        }
    }

    /* přidej počet hran do výstupu */
    *edges_len = count;

    return 0;
}

int compare_edges_id(const void *e1, const void *e2) {

    double e1_w, e2_w;

    e1_w = ((edge *) e1)->id;
    e2_w = ((edge *) e2)->id;

    if (e1_w < e2_w)
        return -1;
    else if (e1_w > e2_w)
        return 1;
    else
        return 0;
}
