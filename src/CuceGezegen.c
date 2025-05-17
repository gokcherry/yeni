#include "CuceGezegen.h"
#include "Gezegen.h"

Gezegen* cuce_olustur(const char* isim, int gun_saat, Zaman tarih) {
    Gezegen* g = gezegen_olustur(isim, CUCE, gun_saat, tarih);

    g->yaslanma_katsayisi = 0.01; // Cüce gezegen için katsayı
    return g;
}
