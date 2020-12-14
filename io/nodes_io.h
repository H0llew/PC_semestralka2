#ifndef NODES_IO_H
#define NODES_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../reader_utils.h"
#include "../graph.h"

/** hlavička souboru */
#define FILE_NODES_HEADER "WKT,id,sname\n"
/** maximální délka jednoho řádku souboru s vrcholy */
#define MAX_SZ_NODES_LENGTH 1000
/** počet sloupců v souboru */
#define COLUMNS 3

/**
 * Zpracuje soubor "file_name" a pokud jsou data souboru validní vrátí je v podobě pole struktur "nodeOLD" o délce "node_len".
 *
 * @param file_name název souboru
 * @param nodes výstupní pole vrcholů
 * @param nodes_len délka výstupního pole vrcholů
 * @return <ul>
 *          <li> 0 -> pokud vše proběhlo v pořádku </li>
 *          <li> 1 -> pokud nebyl nalezen soubor </li>
 *          <li> 2 -> pokud nejsou platné parametry funkce  </li>
 *          <li> 3 -> pokud se nepodařilo soubor načíst </li>
 *          <li> 4 -> pokud se nepodařilo přiřadit paměť </li>
 *         </ul>
 */
unsigned int read_nodes(char *file_name, node **nodes, unsigned int *nodes_len);

/**
 * Zpracuje načtenou řádku na strukturu "nodeOLD".
 * @param line řádka pro zpracování
 * @return vrchol reprezentující stanici, jinak NULL
 */
node *process_node_row(char *line);

#endif
