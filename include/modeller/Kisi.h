#ifndef KISI_H
#define KISI_H

#include "ForwardDefs.h"
#include "UzayGemisi.h"  // Now safe to include since we have forward declarations

typedef struct Kisi {
    char* isim;
    int yas;
    double kalan_omur;
    UzayAraci* arac;
    int yasiyor;
} Kisi;

Kisi* kisi_yarat(const char* isim, int yas, double kalan_omur, UzayAraci* arac);
void kisi_yoket(Kisi* k);

#endif // KISI_H