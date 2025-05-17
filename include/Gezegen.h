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
    char* isim;
    GezegenTipi tip;
    int gun_saat;      // Bir gün kaç saatten oluşuyor
    Zaman tarih;       // Gezegendeki tarih
    double yaslanma_katsayisi; // 0→1.0, 1→0.1, 2→0.5, 3→0.01
} Gezegen;

// Yeni basit oluşturucu
Gezegen* gezegen_olustur(const char* isim,
                       GezegenTipi tip,
                       int gun_saat,
                       Zaman tarih);

// Temizleyici
void gezegen_yoket(Gezegen* g);

#endif // GEZEGEN_H
