/**
*
* @author Gökçe Çiçek Yağmur - gokce.yagmur@ogr.sakarya.edu.tr
* @since Mayıs 2025
* <p>
* Kayaç Gezegen yapısı ve fonksiyonları; Gezegen yapısının bir alt yapısıdır.
* </p>
*/
#include "KayacGezegen.h"
#include "Gezegen.h"

Gezegen* kayac_gezegen_olustur(const char* isim, int gun_saat, Zaman tarih) {
    Gezegen* g = gezegen_olustur(isim, KAYAC, gun_saat, tarih);
    
    g->yaslanma_katsayisi = 1.0;
    return g;
}
