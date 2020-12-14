/**
 * \file edges_io.h
 * \brief Soubor obsahuje definice načítání a zapisování hran
 */

#ifndef EDGES_IO_H
#define EDGES_IO_H

#include "graph.h"

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
