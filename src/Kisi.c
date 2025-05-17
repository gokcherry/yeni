#include "Kisi.h"
#include <stdlib.h>
#include <string.h>

Kisi* kisi_olustur(const char* isim, int yas, double kalan_omur, UzayAraci* arac) {
    Kisi* k = malloc(sizeof(Kisi));
    if (!k) return NULL;
    k->isim       = strdup(isim);
    k->yas        = yas;
    k->kalan_omur = kalan_omur;
    k->arac       = arac;
    k->bulundugu  = NULL;
    k->yasiyor    = 1;
    return k;
}

void kisi_yoket(Kisi* k) {
    if (!k) return;
    free(k->isim);
    free(k);
}
