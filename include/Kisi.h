
#ifndef KISI_H
#define KISI_H
#include "Gezegen.h"
typedef struct UzayAraci UzayAraci;
typedef struct Kisi {
char*      isim;
int        yas;
double     kalan_omur;
UzayAraci* arac;
Gezegen*   bulundugu;  // Bulunduğu gezegen veya NULL
int        yasiyor;
} Kisi;
Kisi* kisi_olustur(const char* isim,
int yas,
double kalan_omur,
UzayAraci* arac);
void  kisi_yoket(Kisi* k);
#endif