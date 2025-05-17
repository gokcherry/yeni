#ifndef KISI_H
#define KISI_H

#include "Gezegen.h"

// Karşılıklı bağımlılığı kırmak için UzayAraci tipi önden bildiriliyor
typedef struct UzayAraci UzayAraci;

// Burada da adımlı struct:
typedef struct Kisi {
    char*      isim;
    int        yas;           // tam yıl
    double     kalan_omur;    // saat cinsinden
    UzayAraci* arac;
    Gezegen*   bulundugu;
    int        yasiyor;       // 1=hayatta, 0=ölü
} Kisi;

Kisi* kisi_olustur(const char* isim,
                   int yas,
                   double kalan_omur,
                   UzayAraci* arac);
void  kisi_yoket(Kisi* k);

#endif // KISI_H
