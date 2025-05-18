/**
*
* @author Gökçe Çiçek Yağmur - gokce.yagmur@ogr.sakarya.edu.tr
* @since Mayıs 2025
* <p>
* Gaz Devi Gezegeni yapısı ve fonksiyonları; Gezegen yapısının bir alt yapısıdır.
* </p>
*/
#include "GazDeviGezegen.h"
#include "Gezegen.h"

Gezegen* gaz_devi_olustur(const char* isim, int gun_saat, Zaman tarih) {
    Gezegen* g = gezegen_olustur(isim, GAZ_DEVI, gun_saat, tarih);

    g->yaslanma_katsayisi = 0.1; 
    return g;
}
