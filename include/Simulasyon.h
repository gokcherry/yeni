#ifndef SIMULASYON_H
#define SIMULASYON_H

#include <stdio.h>        // for FILE
#include "Zaman.h"
#include "Gezegen.h"
#include "UzayGemisi.h"
#include "Kisi.h"

typedef struct Simulasyon {
    Zaman*       zaman;

    int          max_gezegen;
    int          gezegen_sayisi;
    Gezegen**    gezegenler;

    int          max_arac;
    int          arac_sayisi;
    UzayAraci**  araclar;

    int          max_kisi;
    int          kisi_sayisi;
    Kisi**       kisiler;
} Simulasyon;

/* Oluşturma ve temizleme */
Simulasyon* simulasyon_olustur(int max_gezegen,
                                int max_arac,
                                int max_kisi);
void         simulasyon_yoket(Simulasyon* sim);

/* Eleman ekleme */
void simulasyon_gezegen_ekle(Simulasyon* sim, Gezegen* g);
void simulasyon_arac_ekle(Simulasyon* sim, UzayAraci* a);
void simulasyon_kisi_ekle(Simulasyon* sim, Kisi* k);

/* Dosya okuma */
void simulasyon_gezegen_oku(const char* path, Simulasyon* sim);
void simulasyon_arac_oku   (const char* path, Simulasyon* sim);
void simulasyon_kisi_oku   (const char* path, Simulasyon* sim);

/* Simülasyonu çalıştır ve çıktı al */
void simulasyon_calistir(Simulasyon* sim,
                         int gun_sayisi,
                         FILE* cikti_dosyasi);

#endif // SIMULASYON_H
