#include "../../include/modeller/CuceGezegen.h"
#include <stdlib.h>
#include <string.h>

Gezegen* cuce_yarat(const char* isim, double sg, double z) {
    Gezegen* g = (Gezegen*)malloc(sizeof(Gezegen));
    if (g == NULL) return NULL;
    
    g->isim = strdup(isim);
    g->sicaklik_gucu = sg;
    g->zehirlilik = z;
    g->tip = CUCE;
    
    return g;
}