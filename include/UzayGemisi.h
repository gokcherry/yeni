#ifndef UZAYGEMISI_H
#define UZAYGEMISI_H
#include "Gezegen.h"
#include "Zaman.h"
#include "Kisi.h"
typedef enum {
ARAC_BEKLIYOR,
ARAC_YOLDA,
ARAC_VARDI,
ARAC_IMHA
} AracDurum;
typedef struct UzayAraci {
char*     isim;
Gezegen*  cikis;
Gezegen*  hedef;
Zaman*    cikis_tarihi;
int       kalan_sure;
int       toplam_sure;
Kisi**    yolcular;
int       yolcu_sayisi;
AracDurum durum;
} UzayAraci;
UzayAraci* arac_olustur(const char* isim,
Gezegen* cikis,
Gezegen* hedef,
Zaman*   cikis_tarihi,
int      kalan_sure);
void        arac_yoket(UzayAraci* a);
void        arac_yolcu_ekle(UzayAraci* a, Kisi* k);
#endif