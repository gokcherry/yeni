#ifndef UZAY_GEMISI_H
#define UZAY_GEMISI_H

#include "ForwardDefs.h"
#include <stddef.h>

typedef enum {
    UZAY_GEMISI,
    UZAY_ISTASYONU
} AracTipi;

typedef struct UzayAraci {
    char* isim;
    AracTipi tip;
    int max_yolcu;
    int yolcu_sayisi;
    Kisi** yolcular;
    Gezegen* hedef;
    double yakit;
} UzayAraci;

UzayAraci* arac_yarat(const char* isim, AracTipi tip, int max_yolcu, double yakit, Gezegen* hedef);
void arac_yoket(UzayAraci* a);
void arac_yolcu_ekle(UzayAraci* a, Kisi* k);
int arac_yolcu_cikar(UzayAraci* a, Kisi* k);
void arac_hedef_guncelle(UzayAraci* a, Gezegen* g);

#endif // UZAY_GEMISI_H