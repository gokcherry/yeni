#include "../include/araclar/DosyaOkuma.h"
#include "../include/modeller/KayacGezegen.h"
#include "../include/modeller/GazDeviGezegen.h"  
#include "../include/modeller/BuzDeviGezegen.h"
#include "../include/modeller/CuceGezegen.h"
#include <stdlib.h>
#include <string.h>

void veri_oku(const char* dosya_yolu, Simulasyon* sim) {
    FILE* dosya = fopen(dosya_yolu, "r");
    if (!dosya) {
        printf("Dosya açılamadı: %s\n", dosya_yolu);
        return;
    }
    
    char satir[256];
    
    // Dosyayı satır satır oku
    while (fgets(satir, sizeof(satir), dosya)) {
        // Satırın sonundaki yeni satır karakterini temizle
        size_t uzunluk = strlen(satir);
        if (uzunluk > 0 && (satir[uzunluk-1] == '\n' || satir[uzunluk-1] == '\r')) {
            satir[--uzunluk] = '\0';
        }
        
        // Boş satırları atla
        if (uzunluk == 0) continue;
        
        // Veri tipine göre işle
        char veri_tipi[20];
        sscanf(satir, "%s", veri_tipi);
        
        if (strcmp(veri_tipi, "GEZEGEN") == 0) {
            char isim[50];
            char tip_str[20];
            double sg, z;
            
            sscanf(satir, "%*s %s %s %lf %lf", isim, tip_str, &sg, &z);
            
            // Zaman nesnesini oluştur
            Zaman* z_obj = zaman_yarat(2150, 1, 1);
            
            // Gezegen tipini belirle
            GezegenTipi tip;
            Gezegen* g = NULL;
            
            if (strcmp(tip_str, "KAYAC") == 0) {
                tip = KAYAC;
                g = kayac_gec_yarat(isim, sg, z);
            } else if (strcmp(tip_str, "GAZ_DEVI") == 0) {
                tip = GAZ_DEVI;
                g = gaz_devi_yarat(isim, sg, z);
            } else if (strcmp(tip_str, "BUZ_DEVI") == 0) {
                tip = BUZ_DEVI;
                g = buz_devi_yarat(isim, sg, z);
            } else if (strcmp(tip_str, "CUCE") == 0) {
                tip = CUCE;
                g = cuce_yarat(isim, sg, z);
            }
            
            if (g) {
                simulasyon_gezegen_ekle(sim, g);
            }
            
            zaman_yoket(z_obj);
        }
        else if (strcmp(veri_tipi, "ARAC") == 0) {
            char isim[50];
            char tip_str[20];
            int max_yolcu;
            double yakit;
            char hedef_isim[50];
            
            sscanf(satir, "%*s %s %s %d %lf %s", isim, tip_str, &max_yolcu, &yakit, hedef_isim);
            
            // Arac tipini belirle
            AracTipi tip;
            if (strcmp(tip_str, "GEMI") == 0) {
                tip = UZAY_GEMISI;
            } else {
                tip = UZAY_ISTASYONU;
            }
            
            // Hedef gezegeni bul
            Gezegen* hedef = NULL;
            for (int i = 0; i < sim->gezegen_sayisi; i++) {
                if (strcmp(sim->gezegenler[i]->isim, hedef_isim) == 0) {
                    hedef = sim->gezegenler[i];
                    break;
                }
            }
            
            // Aracı oluştur ve simülasyona ekle
            UzayAraci* a = arac_yarat(isim, tip, max_yolcu, yakit, hedef);
            if (a) {
                simulasyon_arac_ekle(sim, a);
            }
        }
        else if (strcmp(veri_tipi, "KISI") == 0) {
            char isim[50];
            int yas;
            double kalan_omur;
            char arac_isim[50];
            
            sscanf(satir, "%*s %s %d %lf %s", isim, &yas, &kalan_omur, arac_isim);
            
            // Aracı bul
            UzayAraci* arac = NULL;
            for (int i = 0; i < sim->arac_sayisi; i++) {
                if (strcmp(sim->araclar[i]->isim, arac_isim) == 0) {
                    arac = sim->araclar[i];
                    break;
                }
            }
            
            // Kişiyi oluştur ve simülasyona ekle
            Kisi* k = kisi_yarat(isim, yas, kalan_omur, arac);
            if (k) {
                simulasyon_kisi_ekle(sim, k);
                // Kişiyi araca ekle
                arac_yolcu_ekle(arac, k);
            }
        }
    }
    
    fclose(dosya);
}