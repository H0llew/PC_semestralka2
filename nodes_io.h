#ifndef NODES_IO_H
#define NODES_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "reader_utils.h"
#include "graph.h"

/** hlavička souboru */
#define FILE_NODES_HEADER "WKT,id,sname\n"
/** maximální délka jednoho řádku souboru s vrcholy */
#define MAX_SZ_NODES_LENGTH 1000
/** počet sloupců v souboru */
#define COLUMNS 3

/**
 * Zpracuje soubor "file_name" a pokud jsou data souboru validní vrátí je v podobě pole struktur vrcholů.
 *
 * @param file_name název souboru
 * @param nodes výstupní pole vrcholů
 * @param nodes_len délka výstupního pole vrcholů
 * @return <ul>
 *          <li> 0 -> vše proběhlo v pořádku </li>
 *          <li> 1 -> špatný soubor </li>
 *          <li> 2 -> chyba čtení souboru </li>
 *         </ul>
 */
unsigned int read_nodes(char *file_name, node **nodes, unsigned int *nodes_len);

/**
 * Zpracuje načtenou řádku na strukturu vrcholu
 *
 * @param line řádka pro zpracování
 * @return vrchol reprezentující stanici, jinak NULL
 */
node *process_node_row(char *line);

#endif
