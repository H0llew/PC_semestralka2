#include "console_input.h"

int *get_input_indexes(unsigned int argc, char *argv[], unsigned int flags_len, char *flags[]) {
    int *res = NULL;
    unsigned int i, fl, exist;

    /* kontrola parametrů */
    if (argc < 2 || !argv || flags_len == 0 || !flags)
        return NULL;

    res = malloc(sizeof(int) * flags_len);
    if (!res)
        return NULL;

    /* vynuluj res */
    for (i = 0; i < flags_len; ++i) {
        res[i] = 0;
    }

    /* projdi vstup z konzole */
    for (i = 1; i < argc; i += 2) {
        exist = 0;

        /* porovnej všechny přepínače s očekávanými přepínači */
        for (fl = 0; fl < flags_len; ++fl) {
            /* porovnej přepínače */
            if (strcmp(flags[fl], argv[i]) == 0) {
                exist = 1;

                /* přepínač nalezen -> existuje hodnota?*/
                if (i + 1 < argc) {
                    res[fl] = (int) i + 1;
                    continue;
                } else {
                    free(res);
                    return NULL;
                }
            }
        }

        /* přepínač nebyl nalezen */
        if (!exist) {
            free(res);
            return NULL;
        }
    }

    return res;
}
