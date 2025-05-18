/**
*
* @author Gökçe Çiçek Yağmur - gokce.yagmur@ogr.sakarya.edu.tr
* @since Mayıs 2025
* <p>
* Kisi header dosyası. Kisi yapısı ve fonksiyonları burada tanımlanır.
* </p>
*/
#ifndef KISI_H
#define KISI_H

#include "Gezegen.h"
typedef struct UzayAraci UzayAraci;

typedef struct Kisi {
    char*      isim;
    int        yas;
    double     kalan_omur;
    UzayAraci* arac;
    Gezegen*   bulundugu;
    int        yasiyor;
} Kisi;

Kisi* kisi_olustur(const char* isim,
                   int yas,
                   double kalan_omur,
                   UzayAraci* arac);
void  kisi_yoket(Kisi* k);

#endif
