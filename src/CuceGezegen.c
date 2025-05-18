/**
*
* @author Gökçe Çiçek Yağmur - gokce.yagmur@ogr.sakarya.edu.tr
* @since Mayıs 2025
* <p>
* Cuce Gezegen yapısı ve fonksiyonları; Gezegen yapısının bir alt yapısıdır.
* </p>
*/
#include "CuceGezegen.h"
#include "Gezegen.h"

Gezegen* cuce_olustur(const char* isim, int gun_saat, Zaman tarih) {
    Gezegen* g = gezegen_olustur(isim, CUCE, gun_saat, tarih);

    g->yaslanma_katsayisi = 0.01;
    return g;
}
