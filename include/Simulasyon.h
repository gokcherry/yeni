/**
*
* @author Gökçe Çiçek Yağmur - gokce.yagmur@ogr.sakarya.edu.tr
* @since Mayıs 2025
* <p>
* Simülasyon header dosyası. Simülasyon yapısı ve fonksiyonları burada tanımlanır.
* </p>
*/
#ifndef SIMULASYON_H
#define SIMULASYON_H

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

Simulasyon* simulasyon_olustur(int max_gezegen,
                               int max_arac,
                               int max_kisi);
void        simulasyon_yoket(Simulasyon* sim);

void simulasyon_gezegen_ekle(Simulasyon* sim, Gezegen* g);
void simulasyon_arac_ekle(Simulasyon* sim, UzayAraci* a);
void simulasyon_kisi_ekle(Simulasyon* sim, Kisi* k);

void simulasyon_gezegen_oku(const char* path, Simulasyon* sim);
void simulasyon_arac_oku   (const char* path, Simulasyon* sim);
void simulasyon_kisi_oku   (const char* path, Simulasyon* sim);
void simulasyon_calistir(Simulasyon* sim);

#endif
