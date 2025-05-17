#include "../../include/modeller/Kisi.h"
#include <stdlib.h>
#include <string.h>


Kisi* kisi_yarat(const char* isim, int yas, double kalan_omur, UzayAraci* arac) {
    Kisi* k = (Kisi*)malloc(sizeof(Kisi));
    k->isim = strdup(isim);
    k->yas = yas;
    k->kalan_omur = kalan_omur;
    k->arac = arac;
    k->yasiyor = 1;  // Başlangıçta kişi hayatta
    
    return k;
}

void kisi_yoket(Kisi* k) {
    if (k) {
        free(k->isim);
        free(k);
    }
}