#include "nodes_io.h"

unsigned int read_nodes(char *file_name, node **nodes, unsigned int *nodes_len) {
    /* čtení */
    FILE *file;
    unsigned int file_length;
    char row[MAX_SZ_NODES_LENGTH];
    unsigned int count,
    int actNode = 0, i;
    int err = 0;
    /* vrcholy */
    node *rows = NULL;
    node *curr = NULL;

    /* kontrola parametrů */
    if (!file_name || !nodes || !nodes_len)
        return 2;

    /* otevři soubor */
    file = fopen(file_name, "r");
    if (!file)
        return 1;

    /* zjisti počet řádek souboru */
    file_length = get_line_count(file);
    if (file_length < 2) {
        /* soubor jen s hlavičkou asi smysl nedává */
        fclose(file);
        return 3;
    }

    /* přiřaď pamět potřebnou pro zpracování a načtení všech řádků */
    rows = malloc(sizeof(node) * file_length);
    if (!rows) {
        fclose(file);
        return 4;
    }

    /* zkontroluj hlavičku souboru */
    fgets(row, MAX_SZ_NODES_LENGTH, file); /* nebude NULL */
    if (strcmp(row, FILE_NODES_HEADER) != 0) {
        free(rows);
        fclose(file);
        return 3;
    }

    /* projdi a zpracuj data souboru */
    actNode = 0;
    while (fgets(row, MAX_SZ_NODES_LENGTH, file) != NULL) {
        curr = process_node_row(row);
        if (!curr) {

            /* IDK it depends.. */
            continue;
        }

        /* vyfiltruj špatná data */

        /* potřebuju minimálně 2 prvky */
        if (actNode > 0) {
            /* id duplicita */
            if (rows[actNode - 1].id == curr->id) {
                free(curr);
                continue; /* SKIP -> id jsou stejné */
            }
        }

        rows[actNode] = *curr;
        free(curr);
        actNode++;
    }

    /*
    for (count = 0; count < actNode; ++count) {
        printf("%u \n", rows[count].id);
    }
     */

    /* zkopíruj pole do outputu */
    *nodes = malloc(sizeof(node) * actNode);
    if (!(*nodes)) {
        fclose(file);
        for (i = 0; i < actNode; ++i) {
            free(rows[i].name);
        }
        free(rows);
        return 3;
    }

    memcpy(*nodes, rows, sizeof(node) * actNode);
    *nodes_len = actNode;

    /*
    for (actNode = 0; actNode < *node_len; ++actNode) {
        printf("%u \n", output[actNode].id);
    }
    */

    /* uvolni paměť */

    fclose(file);
    free(rows);

    return 0;
}

node *process_node_row(char *line) {
    unsigned int step = 0;
    char *wkt_token, *p_end, *p_end2;
    char cols[COLUMNS][MAX_SZ_NODES_LENGTH];
    /* prvky vrcholu */
    double x, y;
    unsigned int id;
    /* vrchol */
    node *n = NULL;

    /* pro rozdělení řádky */
    char *token = NULL;

    /* ověření parametrů */
    if (!line)
        return NULL;

    /* zpracování řádky -> prvně rozdělíme */
    token = strtok(line, ",");
    if (!token)
        return NULL;

    /* 3 kroky (WTD, id a nakonec sname) */
    while (token != NULL) {
        if (step >= COLUMNS)
            return NULL;

        strcpy(cols[step], token);

        token = strtok(NULL, ",");
        step++;
    }
    /* kontrola řádky */
    if (step < 2)
        return NULL;
    /* očekáváme že název stanice nebyl zadán */
    if (step == 2)
        strcpy(cols[2], " ");

    /* zpracuj prvky "cols" */

    /* WKT */
    wkt_token = strtok(cols[0], "(");
    wkt_token = strtok(NULL, ")");

    /* WKT x */
    x = strtod(wkt_token, &p_end);
    if (x == 0 && (errno != 0 || p_end == wkt_token))
        return NULL;
    /* WKT y */
    y = strtod(p_end, &p_end2);
    if (y == 0 && (errno != 0 || p_end2 == p_end))
        return NULL;

    /* id */
    id = strtol(cols[1], &p_end, 10);
    if (id == 0 && (errno != 0 || p_end == cols[1]))
        return NULL;

    /* vytvoř vrchol a vlož do něj prvky řádku */
    n = malloc(sizeof(node));
    if (!n) {
        return NULL;
    }

    n->latitude = x;
    n->longitude = y;
    n->id = id;
    n->component = -1;
    /* strcpy(n->name, cols[2]); */
    n->name = malloc(sizeof(char) * (strlen(cols[2]) + 1));
    if (!n->name) {
        free(n);
        return NULL;
    }
    strcpy(n->name, cols[2]);

    return n;
}
