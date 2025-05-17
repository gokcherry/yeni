#ifndef UZAYGEMISI_H
#define UZAYGEMISI_H

#include "Gezegen.h"
#include "Zaman.h"

// Karşılıklı bağımlılığı kırmak için Kisi tipi önden bildiriliyor
typedef struct Kisi Kisi;

// Burada struct anons değil, adımlı struct kullanıyoruz:
typedef struct UzayAraci {
    char*     isim;
    Gezegen*  cikis;
    Gezegen*  hedef;
    Zaman*    cikis_tarihi;
    int       kalan_sure;    // saat cinsinden
    Kisi**    yolcular;
    int       yolcu_sayisi;
} UzayAraci;

UzayAraci* arac_olustur(const char* isim,
                        Gezegen* cikis,
                        Gezegen* hedef,
                        Zaman*   cikis_tarihi,
                        int      kalan_sure);
void        arac_yoket(UzayAraci* a);
void        arac_yolcu_ekle(UzayAraci* a, Kisi* k);

#endif // UZAYGEMISI_H
