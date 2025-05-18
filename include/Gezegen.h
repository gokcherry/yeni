/**
*
* @author Gökçe Çiçek Yağmur - gokce.yagmur@ogr.sakarya.edu.tr
* @since Mayıs 2025
* <p>
* Gezegen header dosyası. Gezegen yapısı ve fonksiyonları burada tanımlanır.
* </p>
*/
#ifndef GEZEGEN_H
#define GEZEGEN_H

#include "Zaman.h"

typedef enum {
    KAYAC = 0,
    GAZ_DEVI = 1,
    BUZ_DEVI = 2,
    CUCE = 3
} GezegenTipi;

typedef struct {
    char*      isim;
    GezegenTipi tip;
    int        gun_saat;            // Bir günün saat cinsinden uzunluğu
    Zaman      tarih;               // Gezegenin güncel tarihi
    double     yaslanma_katsayisi;  // Yaşlanma katsayısı
} Gezegen;

Gezegen* gezegen_olustur(const char* isim,
                         GezegenTipi tip,
                         int gun_saat,
                         Zaman tarih);
void     gezegen_yoket(Gezegen* g);

#endif
