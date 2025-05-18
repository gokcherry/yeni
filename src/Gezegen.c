
#include <stdlib.h>
#include <string.h>
#include "Gezegen.h"
static double tip_to_katsayi(GezegenTipi tip) {
switch (tip) {
case KAYAC:    return 1.0;
case GAZ_DEVI: return 0.1;
case BUZ_DEVI: return 0.5;
case CUCE:     return 0.01;
default:       return 1.0;
}
}
Gezegen* gezegen_olustur(const char* isim,
GezegenTipi tip,
int gun_saat,
Zaman tarih) {
Gezegen* g = malloc(sizeof(Gezegen));
g->isim               = strdup(isim);
g->tip                = tip;
g->gun_saat           = gun_saat;
g->tarih              = tarih;
g->yaslanma_katsayisi = tip_to_katsayi(tip);
return g;
}
void gezegen_yoket(Gezegen* g) {
if (!g) return;
free(g->isim);
free(g);
}