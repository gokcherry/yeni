#include "UzayGemisi.h"
#include <stdlib.h>
#include <string.h>

UzayAraci* arac_olustur(const char* isim,
                      Gezegen* cikis,
                      Gezegen* hedef,
                      Zaman* cikis_tarihi,
                      int kalan_sure) {
    UzayAraci* a = malloc(sizeof(UzayAraci));
    if (!a) return NULL;
    a->isim         = strdup(isim);
    a->cikis        = cikis;
    a->hedef        = hedef;
    a->cikis_tarihi = cikis_tarihi;
    a->kalan_sure   = kalan_sure;
    a->yolcu_sayisi = 0;
    // Yolcu kapasitesini simülasyondan bilmediğimiz için,
    // en fazla  sim->max_kisi kadar tutacağız:
    a->yolcular     = NULL;  // simulasyon_oku sırasında allocate edilecek
    return a;
}

void arac_yoket(UzayAraci* a) {
    if (!a) return;
    free(a->isim);
    if (a->kalan_sure > 0 && a->cikis_tarihi)
        zaman_yoket(a->cikis_tarihi);
    if (a->yolcular) free(a->yolcular);
    free(a);
}

void arac_yolcu_ekle(UzayAraci* a, Kisi* k) {
    if (!a || !k) return;
    if (!a->yolcular) return;
    a->yolcular[a->yolcu_sayisi++] = k;
}
