#include "edges_reader.h"

int read_edges(char *file_name, edge **edges, unsigned int *edges_len) {
    FILE *file;
    unsigned int file_length;
    edge *rows = NULL, *curr = NULL;
    int actEdge, i, err = 0;
    char row[MAX_SZ_EDGE_LENGTH];
    unsigned int *matrix = NULL;

    /* kontrola parametrů */
    if (!file_name || !edges || !edges_len)
        return 2;

    /* otevři soubor */
    file = fopen(file_name, "r");
    if (!file)
        return 1;

    /* zjisti počet řádků v souboru */
    file_length = get_line_count(file);
    if (file_length < 2) {
        /* soubor jen s hlavičkou asi smysl nedává */
        fclose(file);
        return 3;
    }

    /* přiřaď pamět potřebnou pro zpracování a načtení všech řádků */
    rows = malloc(sizeof(edge) * file_length);
    if (!rows) {
        fclose(file);
        return 4;
    }

    /* zkontroluj hlavičku souboru */
    fgets(row, MAX_SZ_EDGE_LENGTH, file); /* nebude NULL */
    if ((strcmp(row, FILE_HEADER_EDGES_1) != 0) && (strcmp(row, FILE_HEADER_EDGES_2) != 0)) {
        free(rows);
        fclose(file);
        return 3;
    }

    /* projdi a zpracuj data souboru */
    actEdge = 0;
    while (fgets(row, MAX_SZ_EDGE_LENGTH, file) != NULL) {
        curr = process_edge_row(row, &err);
        if (!curr) {
            /* free */
            /*
            free(rows);
            return (err == 1) ? 4 : 3;
             */
            /* IDK it depends... 0*/
            continue;
        }

        /* vyfiltruj špatná data */

        /* 0 délka */
        if (curr->weight == 0) {
            free(curr->wkt);
            free(curr->nation_name);
            free(curr);
            continue;
        }
        /* hrana {u,u} */
        if (curr->target == curr->source) {
            free(curr->wkt);
            free(curr->nation_name);
            free(curr);
            continue;
        }

        if (actEdge > 0) {
            /* id duplicita */
            if (rows[actEdge - 1].id == curr->id) {
                free(curr->wkt);
                free(curr->nation_name);
                free(curr);
                continue;
            }
            /* hrana již existuje */
            if (checkIfExist(rows, actEdge, curr->source, curr->target) == 1) {
                free(curr->wkt);
                free(curr->nation_name);
                free(curr);
                continue;
            }
        }

        rows[actEdge] = *curr;
        free(curr);
        actEdge++;
    }

    /* zkopíruj pole do outputu */
    *edges = malloc(sizeof(edge) * actEdge);
    if (!(*edges)) {
        free(rows);
        fclose(file);
        return 3;
    }

    memcpy(*edges, rows, sizeof(edge) * actEdge);
    *edges_len = actEdge;

    /* uvolni paměť */
    free(rows);

    fclose(file);

    return 0;
}

edge *process_edge_row(char *line, int *flag) {
    int col, i;
    char wkt[MAX_WKT_LENGTH] = {0}, cols_value[EDGE_COLUMNS - 1][MAX_REST_LENGTH];
    edge *res;
    char *p_end;
    /* prvky hrany */
    unsigned int id, nation_id, source, target;
    double length;

    /* pro rozdělení řádky */
    char *token = NULL;

    /* ověření parametrů */
    if (!line || !flag)
        return NULL;

    /* dostaň WKT */
    token = strtok(line, "\"");
    if (!token)
        return NULL;
    strcpy(wkt, token);

    /* nyní můžeme oddělovat pomocí čárek */
    for (col = 1; col < EDGE_COLUMNS; ++col) {
        if (token == NULL) {
            --col;
            break;
        }

        token = strtok(NULL, ",");
        if (strcmp(token, "\n") == 0) {
            --col;
            break;
        }

        strcpy(cols_value[col - 1], token);
        /* printf("%d %s \n", col - 1, token); */
    }
    /* kontrola parsovaných dat */
    if (col < (EDGE_COLUMNS - 2)) {
        /* špatná data */
        return NULL;
    }
    if (col < EDGE_COLUMNS - 1) {
        /* pravděpodobně nebyl zadán stát (snad jen ten nemůže být zadán )*/
        /* posuň prvky o 1 => od sname */
        for (i = EDGE_COLUMNS - 2; i >= 2; --i) {
            strcpy(cols_value[i], cols_value[i - 1]);
        }
        strcpy(cols_value[2], "");
    }

    id = strtol(cols_value[0], &p_end, 10);
    if (id == 0 && (errno != 0 || p_end == cols_value[0]))
        return NULL;

    nation_id = strtol(cols_value[1], &p_end, 10);
    if (nation_id == 0 && (errno != 0 || p_end == cols_value[1]))
        return NULL;

    source = strtol(cols_value[3], &p_end, 10);
    if (source == 0 && (errno != 0 || p_end == cols_value[3]))
        return NULL;

    target = strtol(cols_value[4], &p_end, 10);
    if (target == 0 && (errno != 0 || p_end == cols_value[4]))
        return NULL;

    length = strtod(cols_value[5], &p_end);
    if (length == 0 && (errno != 0 || p_end == cols_value[5]))
        return NULL;

    /* vytvoř hranu a vlož do ní data */
    res = malloc(sizeof(edge));
    if (!res) {
        *flag = 1;
        return NULL;
    }

    res->wkt = malloc(sizeof(char) * (strlen(wkt) + 1));
    if (!res->wkt) {
        *flag = 1;
        free(res);
        return NULL;
    }

    res->nation_name = malloc(sizeof(char) * (strlen(cols_value[2]) + 1));
    if (!res->nation_name) {
        *flag = 1;
        free(res->wkt);
        free(res);
        return NULL;
    }

    strcpy(res->wkt, wkt);
    strcpy(res->nation_name, cols_value[2]);

    /* strcpy(res->WKT, wkt); */
    res->id = id;
    res->nation_id = nation_id;
    /* strcpy(res->nation_name, cols_value[2]); */
    res->source = source;
    res->target = target;
    res->weight = length;
    res->component = -1;

    /* kontrolní výpis */
    /*
    for (i = 0; i < EDGE_COLUMNS - 1; ++i) {
        printf("%s \n", cols_value[i]);
    }
    printf("K %d \n", col);
    printf("K %s \n", wkt);
    */

    return res;
}

int checkIfExist(edge *rows, unsigned int rows_len, unsigned int source, unsigned int target) {
    unsigned int i;

    /* kontrola parametrů */
    if (!rows || rows_len == 0 || source == 0 || target == 0)
        return 1;

    for (i = 0; i < rows_len; ++i) {
        if (((source == rows[i].source) && (target == rows[i].target)) ||
            ((source == rows[i].target) && (target == rows[i].source)))
            return 1;
    }

    return 0;
}
