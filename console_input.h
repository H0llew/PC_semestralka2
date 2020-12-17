#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H

#include <stdlib.h>
#include <string.h>

/**
 * Funkce prochází vstupní pole "argv" a hledá v něm hodnoty přepínačů zadaných ve "flags".
 * Pozice nalezených pozic ve vraceném poli odpovídá pozici přepínače ve "flags".
 * Možné hodnoty výstupního pole jsou:   0 => přepínač nebyl zadán
 *                                      >0 => pozice hledané hodnoty přepínače
 * @param argc velikost pole "argc"
 * @param argv vstupní pole s přepínači a jejich hodnotami
 * @param flags_len velikost pole "flags"
 * @param flags pole hledaných přepínačů
 * @return pole pozic hodnot přepínačů na idexu odpovídající pozici přepínače ve "flags",
 *         nebo null pokud byly zadány neplatné parametry, nebo neznámý přepínač
 */
int *get_input_indexes(unsigned int argc, char *argv[], unsigned int flags_len, char *flags[]);

#endif
