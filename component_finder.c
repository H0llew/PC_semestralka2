#include "component_finder.h"

void find_neighbours(unsigned int n,
                     edge *edges, unsigned int edges_len,
                     node *nodes, unsigned int nodes_len,
                     unsigned int **neighbours, unsigned int *neighbours_len,
                     int component) {

    unsigned int *nbs_temp = NULL, nbs_count, i;

    /* kontrola parametrů */
    if (!edges || edges_len == 0 || !neighbours || !neighbours_len)
        return;

    /* nainicializuj dočasné pole sousedů na max. možný počet sousedů */
    nbs_temp = malloc(sizeof(unsigned int) * edges_len);
    if (!nbs_temp)
        return;

    nbs_count = 0;
    /* hledání sousedů */
    for (i = 0; i < edges_len; ++i) {
        edge curr = edges[i];
        /* najdi zda v hraně je hledaný vrchol */
        if (curr.target == n || curr.source == n) {
            /* v hraně je hledaný vrchol => hrana patří do stejné komponenty jako zadaný vrchol*/
            edges[i].component = component;
            nodes[get_node_pos(curr.target, nodes, nodes_len)].component = component;
            nodes[get_node_pos(curr.source, nodes, nodes_len)].component = component;

            /* přidej souseda to dočasného pole sousedů */
            nbs_temp[nbs_count] = (curr.target == n) ? curr.source : curr.target;
            nbs_count++;
        }
    }

    /* máme sousedy teď uvolníme přebytečnou paměť a výsledek zapíšeme do pole sousedů */
    *neighbours_len = nbs_count;
    if (nbs_count != 0) {
        *neighbours = malloc(sizeof(unsigned int) * nbs_count);
        if (!(*neighbours)) {
            free(nbs_temp);
            return;
        }

        memcpy(*neighbours, nbs_temp, sizeof(unsigned int) * nbs_count);
    }

    free(nbs_temp);
}

void dfs(unsigned int n, unsigned int *mark,
         edge *edges, unsigned int edges_len,
         node *nodes, unsigned int nodes_len,
         int component) {

    unsigned int *neighbours = NULL, neighbour_len, i, neighbour;
    int pos, pos_nb;

    /* kontrola parametrů */
    if (!mark || !edges || edges_len == 0 || !nodes || nodes_len == 0)
        return;

    pos = get_node_pos(n, nodes, nodes_len);
    if (pos < 0)
        return;

    /* zpracuj vrchol */
    mark[pos] = 1;
    find_neighbours(n, edges, edges_len, nodes, nodes_len, &neighbours, &neighbour_len, component);
    for (i = 0; i < neighbour_len; ++i) {
        neighbour = neighbours[i];
        pos_nb = get_node_pos(neighbour, nodes, nodes_len);
        if (pos_nb < 0)
            return;

        if (mark[pos_nb] == 0)
            dfs(neighbour, mark, edges, edges_len, nodes, nodes_len, component);
    }

    mark[pos] = 2;
}

int find_components(node *nodes, unsigned int nodes_len, edge *edges, unsigned int edges_len) {

    unsigned int i, comps, *marks = NULL;

    /* kontrola parametrů */
    if (!nodes || nodes_len == 0 || !edges || edges_len == 0)
        return -1;

    /* vytvoř pole obarvení vrcholů */
    marks = malloc(sizeof(unsigned int) * nodes_len);
    if (!marks)
        return -1;
    /* vynuluj marks */
    for (i = 0; i < nodes_len; ++i) {
        marks[i] = 0;
    }

    /* přiřaď hranám jejich id komponenty ve které se nacházejí */
    comps = 0;
    for (i = 0; i < nodes_len; ++i) {
        if (marks[i] == 0) {
            dfs(nodes[i].id, marks, edges, edges_len, nodes, nodes_len, (int) comps);
            comps++;
        }
    }

    return (int) comps;
}
