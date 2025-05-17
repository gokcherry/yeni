#ifndef SIMULASYON_H
#define SIMULASYON_H

#include "../modeller/Zaman.h"
#include "../modeller/Gezegen.h"
#include "../modeller/UzayGemisi.h"
#include <stdio.h>

typedef struct {
    Zaman* zaman;
    int gezegen_sayisi;
    int max_gezegen;
    Gezegen** gezegenler;
    
    int arac_sayisi;
    int max_arac;
    UzayAraci** araclar;
    
    int kisi_sayisi;
    int max_kisi;
    Kisi** kisiler;
} Simulasyon;

Simulasyon* simulasyon_yarat(int max_gezegen, int max_arac, int max_kisi);
void simulasyon_yoket(Simulasyon* sim);
void simulasyon_gezegen_ekle(Simulasyon* sim, Gezegen* g);
void simulasyon_arac_ekle(Simulasyon* sim, UzayAraci* a);
void simulasyon_kisi_ekle(Simulasyon* sim, Kisi* k);
void simulasyon_calistir(Simulasyon* sim, int gun_sayisi, FILE* cikti_dosyasi);

#endif // SIMULASYON_H