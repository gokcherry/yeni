
#include "BuzDeviGezegen.h"
#include "Gezegen.h"

Gezegen* buz_devi_olustur(const char* isim, int gun_saat, Zaman tarih) {
    Gezegen* g = gezegen_olustur(isim, BUZ_DEVI, gun_saat, tarih);

    g->yaslanma_katsayisi = 0.5; 
    return g;
}
