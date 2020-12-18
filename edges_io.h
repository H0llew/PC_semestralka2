/**
 * \file edges_io.h
 * \brief Soubor obsahuje definice načítání a zapisování hran
 */

#ifndef EDGES_IO_H
#define EDGES_IO_H

#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "graph.h"
#include "reader_utils.h"

/** hlavička souboru 1 */
#define FILE_HEADER_EDGES_1 "WKT,id,nation,cntryname,source,target,clength,,,,,,,,,,,,,,,,,,\n"
/** hlavička souboru 2 */
#define FILE_HEADER_EDGES_2 "WKT,id,nation,cntryname,source,target,clength\n"
/** maximální délka jednoho řádku souboru s hranama */
#define MAX_EDGES_ROW_LENGTH 20000
/** maximální délka WKT (max. délka v datech byla ~12500)*/
#define MAX_WKT_LENGTH 15000
/** maximální délka pro ostatní data */
#define MAX_REST_LENGTH 5000
/** počet prohledávaných sloupců řádku */
#define EDGE_COLUMNS 7

/**
 * Zpracuje soubor "file_name" a pokud jsou data souboru validní vrátí je v podobě pole struktur hran.
 *
 * @param file_name název souboru
 * @param output výstupní pole hran
 * @param edge_len délka výstupního pole hran
 * @param maxIdOfNodes nejvyšší id vrcholu
 * @return <ul>
 *          <li> 0 -> vše proběhlo v pořádku </li>
 *          <li> 1 -> špatný soubor </li>
 *          <li> 2 -> chyba čtení souboru </li>
 *         </ul>
 */
int read_edges(char *file_name, edge **edges, unsigned int *edges_len);

/**
 * Zpracuje načtenou řádku na strukturu hrany.
 *
 * @param line řádka pro zpracování
 * @return vrchol reprezentující hranu železniční sítě, jinak NULL
 */
edge *process_edge_row(char *line);

/**
 * Zkontrolu zda již existuje hrana {u,v}
 *
 * @param rows řádky
 * @param rows_len počet řádků
 * @param source odkud
 * @param target kam
 *
 * @return 0, pokud se hrana ještě neexistuje, jinak -1
 */
int check_if_exist(edge *rows, unsigned int rows_len, unsigned int source, unsigned int target);

/**
 * Zapíše poskytnuté hrany do souboru "file_name".
 *
 * @param file_name název výstupního souboru
 * @param edges pole hran
 * @param edges_len délka pole hran
 *
 * @return 0, pokud se zápis povedl, jinak -1
 */
int create_edges_file(char *file_name, edge *edges, unsigned int edges_len);

#endif
