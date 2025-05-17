#include "../../include/modeller/Gezegen.h"
#include <stdlib.h>
#include <string.h>

Gezegen* gezegen_yarat(const char* isim, GezegenTipi tip, double sg, double z) {
    Gezegen* g = (Gezegen*)malloc(sizeof(Gezegen));
    if (g == NULL) return NULL;
    
    g->isim = strdup(isim);
    g->tip = tip;
    g->sicaklik_gucu = sg;
    g->zehirlilik = z;
    
    return g;
}

void gezegen_yoket(Gezegen* g) {
    if (g) {
        free(g->isim);
        free(g);
    }
}