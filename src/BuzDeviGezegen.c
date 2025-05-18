/**
*
* @author Gökçe Çiçek Yağmur - gokce.yagmur@ogr.sakarya.edu.tr
* @since Mayıs 2025
* <p>
* Buz Devi Gezegen yapısı ve fonksiyonları; Gezegen yapısının bir alt yapısıdır.
* </p>
*/
#include "BuzDeviGezegen.h"
#include "Gezegen.h"

Gezegen* buz_devi_olustur(const char* isim, int gun_saat, Zaman tarih) {
    Gezegen* g = gezegen_olustur(isim, BUZ_DEVI, gun_saat, tarih);

    g->yaslanma_katsayisi = 0.5; 
    return g;
}
