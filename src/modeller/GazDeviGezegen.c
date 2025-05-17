#include "../../include/modeller/GazDeviGezegen.h"
#include <stdlib.h>
#include <string.h>

Gezegen* gaz_devi_yarat(const char* isim, double sg, double z) {
    Gezegen* g = (Gezegen*)malloc(sizeof(Gezegen));
    if (g == NULL) return NULL;
    
    g->isim = strdup(isim);
    g->sicaklik_gucu = sg;
    g->zehirlilik = z;
    g->tip = GAZ_DEVI;
    
    return g;
}