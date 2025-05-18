/**
*
* @author Gökçe Çiçek Yağmur - gokce.yagmur@ogr.sakarya.edu.tr
* @since Mayıs 2025
* <p>
* Kisi yapısı ve fonksiyonları
* </p>
*/
#include <stdlib.h>
#include <string.h>
#include "Kisi.h"
#include "UzayGemisi.h" 

Kisi* kisi_olustur(const char* isim, int yas, double kalan_omur, UzayAraci* arac) {
    Kisi* k = malloc(sizeof(Kisi));
    k->isim       = strdup(isim);
    k->yas        = yas;
    k->kalan_omur = kalan_omur;
    k->arac       = arac;
    k->bulundugu  = arac->cikis;
    k->yasiyor    = 1;
    return k;
}

void kisi_yoket(Kisi* k) {
    if (!k) return;
    free(k->isim);
    free(k);
}
