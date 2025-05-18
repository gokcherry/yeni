/**
*
* @author Gökçe Çiçek Yağmur - gokce.yagmur@ogr.sakarya.edu.tr
* @since Mayıs 2025
* <p>
* Uzay Gemisi\Aracı yapısı ve fonksiyonları
* </p>
*/
#include <stdlib.h>
#include <string.h>
#include "UzayGemisi.h"

UzayAraci* arac_olustur(const char* isim,
                        Gezegen* cikis,
                        Gezegen* hedef,
                        Zaman*   cikis_tarihi,
                        int      kalan_sure) {
    UzayAraci* a = malloc(sizeof(UzayAraci));
    a->isim         = strdup(isim);
    a->cikis        = cikis;
    a->hedef        = hedef;
    a->cikis_tarihi = cikis_tarihi;
    a->kalan_sure   = kalan_sure;
    a->toplam_sure  = kalan_sure;
    a->yolcular     = calloc(10, sizeof(Kisi*));
    a->yolcu_sayisi = 0;
    a->durum        = ARAC_BEKLIYOR;
    return a;
}

void arac_yoket(UzayAraci* a) {
    if (!a) return;
    free(a->isim);
    if ((a->durum == ARAC_BEKLIYOR || a->durum == ARAC_YOLDA) && a->cikis_tarihi) {
        zaman_yoket(a->cikis_tarihi);
    }
    if (a->yolcular) free(a->yolcular);
    free(a);
}

void arac_yolcu_ekle(UzayAraci* a, Kisi* k) {
    if (!a || !k) return;
    a->yolcular[a->yolcu_sayisi++] = k;
}
