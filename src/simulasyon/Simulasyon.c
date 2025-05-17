#include "../../include/simulasyon/Simulasyon.h"
#include "../../include/modeller/Kisi.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>    // for strdup

Simulasyon* simulasyon_yarat(int max_gezegen, int max_arac, int max_kisi) {
    Simulasyon* sim = (Simulasyon*)malloc(sizeof(Simulasyon));
    if (sim == NULL) return NULL;
    
    sim->zaman = zaman_yarat(2150, 1, 1);
    if (sim->zaman == NULL) {
        free(sim);
        return NULL;
    }
    
    sim->max_gezegen = max_gezegen;
    sim->gezegen_sayisi = 0;
    sim->gezegenler = (Gezegen**)malloc(sizeof(Gezegen*) * max_gezegen);
    if (sim->gezegenler == NULL) {
        zaman_yoket(sim->zaman);
        free(sim);
        return NULL;
    }
    
    sim->max_arac = max_arac;
    sim->arac_sayisi = 0;
    sim->araclar = (UzayAraci**)malloc(sizeof(UzayAraci*) * max_arac);
    if (sim->araclar == NULL) {
        free(sim->gezegenler);
        zaman_yoket(sim->zaman);
        free(sim);
        return NULL;
    }
    
    sim->max_kisi = max_kisi;
    sim->kisi_sayisi = 0;
    sim->kisiler = (Kisi**)malloc(sizeof(Kisi*) * max_kisi);
    if (sim->kisiler == NULL) {
        free(sim->araclar);
        free(sim->gezegenler);
        zaman_yoket(sim->zaman);
        free(sim);
        return NULL;
    }
    
    return sim;
}

void simulasyon_yoket(Simulasyon* sim) {
    if (sim) {
        // Tüm gezegenleri temizle
        for (int i = 0; i < sim->gezegen_sayisi; i++) {
            gezegen_yoket(sim->gezegenler[i]);
        }
        free(sim->gezegenler);
        
        // Tüm araçları temizle
        for (int i = 0; i < sim->arac_sayisi; i++) {
            arac_yoket(sim->araclar[i]);
        }
        free(sim->araclar);
        
        // Tüm kişileri temizle
        for (int i = 0; i < sim->kisi_sayisi; i++) {
            kisi_yoket(sim->kisiler[i]);
        }
        free(sim->kisiler);
        
        zaman_yoket(sim->zaman);
        free(sim);
    }
}

void simulasyon_gezegen_ekle(Simulasyon* sim, Gezegen* g) {
    if (!sim || !g || sim->gezegen_sayisi >= sim->max_gezegen) return;
    
    sim->gezegenler[sim->gezegen_sayisi++] = g;
}

void simulasyon_arac_ekle(Simulasyon* sim, UzayAraci* a) {
    if (!sim || !a || sim->arac_sayisi >= sim->max_arac) return;
    
    sim->araclar[sim->arac_sayisi++] = a;
}

void simulasyon_kisi_ekle(Simulasyon* sim, Kisi* k) {
    if (!sim || !k || sim->kisi_sayisi >= sim->max_kisi) return;
    
    sim->kisiler[sim->kisi_sayisi++] = k;
}

void simulasyon_calistir(Simulasyon* sim, int gun_sayisi, FILE* cikti_dosyasi) {
    if (!sim || !cikti_dosyasi) return;
    
    fprintf(cikti_dosyasi, "Simulasyon başlıyor...\n");
    fprintf(cikti_dosyasi, "Başlangıç tarihi: %d/%d/%d\n", 
            sim->zaman->gun, sim->zaman->ay, sim->zaman->yil);
    
    // Her gün için simulasyonu çalıştır
    for (int gun = 1; gun <= gun_sayisi; gun++) {
        // Zamanı ilerlet
        zaman_ilerlet(sim->zaman, 1);
        
        fprintf(cikti_dosyasi, "\nGün %d (%d/%d/%d):\n", 
                gun, sim->zaman->gun, sim->zaman->ay, sim->zaman->yil);
        
        // Kişilerin durumunu güncelle
        for (int i = 0; i < sim->kisi_sayisi; i++) {
            Kisi* k = sim->kisiler[i];
            
            // Eğer kişi hayatta değilse devam et
            if (!k->yasiyor) continue;
            
            // Kalan ömrü azalt
            k->kalan_omur -= 1.0;
            
            // Eğer kalan ömür 0'a ulaştıysa kişi ölür
            if (k->kalan_omur <= 0) {
                k->yasiyor = 0;
                fprintf(cikti_dosyasi, "- %s öldü (yaş: %d).\n", k->isim, k->yas);
            }
            
            // Kişinin yaşını güncelle
            // Her yıl bir yaş ekle (30 günde bir)
            if (gun % 30 == 0) {
                k->yas++;
            }
        }
        
        // Araçların durumlarını güncelle ve raporla
        for (int i = 0; i < sim->arac_sayisi; i++) {
            UzayAraci* a = sim->araclar[i];
            
            // Yakıt tüketimi simülasyonu
            a->yakit -= 0.5;
            if (a->yakit < 0) a->yakit = 0;
            
            // Hayatta kalan yolcu sayısını hesapla
            int hayatta = 0;
            for (int j = 0; j < a->max_yolcu; j++) {
                if (a->yolcular[j] && a->yolcular[j]->yasiyor) hayatta++;
            }
            
            fprintf(cikti_dosyasi, "- %s: %d/%d yolcu hayatta, %.2f birim yakıt kaldı.\n", 
                   a->isim, hayatta, a->yolcu_sayisi, a->yakit);
        }
    }
    
    fprintf(cikti_dosyasi, "\nSimulasyon tamamlandı.\n");
    fprintf(cikti_dosyasi, "Bitiş tarihi: %d/%d/%d\n", 
            sim->zaman->gun, sim->zaman->ay, sim->zaman->yil);
    
    // Hayatta kalan kişilerin durumunu raporla
    int hayatta_kalanlar = 0;
    for (int i = 0; i < sim->kisi_sayisi; i++) {
        if (sim->kisiler[i]->yasiyor) hayatta_kalanlar++;
    }
    
    fprintf(cikti_dosyasi, "Toplam kişi sayısı: %d\n", sim->kisi_sayisi);
    fprintf(cikti_dosyasi, "Hayatta kalanlar: %d (%%%d)\n", 
            hayatta_kalanlar, 
            (sim->kisi_sayisi > 0) ? (hayatta_kalanlar * 100 / sim->kisi_sayisi) : 0);
}