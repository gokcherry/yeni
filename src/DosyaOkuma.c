/**
*
* @author Gökçe Çiçek Yağmur - gokce.yagmur@ogr.sakarya.edu.tr
* @since Mayıs 2025
* <p>
* Dosya Okuma yapısı ve fonksiyonları. 
* </p>
*/
#include "DosyaOkuma.h"
#include "Simulasyon.h"
#include "KayacGezegen.h"
#include "GazDeviGezegen.h"
#include "BuzDeviGezegen.h"
#include "CuceGezegen.h"
#include "UzayGemisi.h"
#include "Kisi.h"
#include "Zaman.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Gezegen* bul_gezegen(Simulasyon* sim, const char* isim) {
    if (!sim || !isim) return NULL;
    
    for (int i = 0; i < sim->gezegen_sayisi; i++) {
        if (sim->gezegenler[i] && strcmp(sim->gezegenler[i]->isim, isim) == 0)
            return sim->gezegenler[i];
    }
    return NULL;
}

static UzayAraci* bul_arac(Simulasyon* sim, const char* isim) {
    if (!sim || !isim) return NULL;
    
    for (int i = 0; i < sim->arac_sayisi; i++) {
        if (sim->araclar[i] && strcmp(sim->araclar[i]->isim, isim) == 0)
            return sim->araclar[i];
    }
    return NULL;
}

void veri_oku(const char* dosya_yolu, Simulasyon* sim) {
    if (!dosya_yolu || !sim) {
        printf("Gecersiz parametreler\n");
        return;
    }
    
    FILE* dosya = fopen(dosya_yolu, "r");
    if (!dosya) {
        printf("Dosya açılamadı: %s\n", dosya_yolu);
        return;
    }

    char satir[256];
    while (fgets(satir, sizeof(satir), dosya)) {
        
        satir[strcspn(satir, "\r\n")] = '\0';
        if (!satir[0]) continue; 

        int alan = 0;
        char* tmp = strdup(satir);
        if (!tmp) {
            printf("Bellek hatasi\n");
            continue;
        }
        
        for (char* t = strtok(tmp, "#"); t; t = strtok(NULL, "#"))
            alan++;
        free(tmp);

        char* flds[5] = {0};
        char* p = strtok(satir, "#");
        for (int i = 0; p && i < alan; i++) {
            flds[i] = p;
            p = strtok(NULL, "#");
        }

        if (alan == 4) {
            // GEZEGEN veya KISI
            int maybeTip = atoi(flds[1]);
            if (maybeTip >= 0 && maybeTip <= 3) {
                // GEZEGEN: isim#tip#saat#günlük_tarih
                const char* isim     = flds[0];
                int         tip      = maybeTip;
                int         gun_saat = atoi(flds[2]);
                int g, m, y;
                sscanf(flds[3], "%d.%d.%d", &g, &m, &y);
                Zaman z = { .yil = y, .ay = m, .gun = g, .saat = 0 };

                Gezegen* gg = NULL;
                switch (tip) {
                    case 0: gg = kayac_gezegen_olustur(isim, gun_saat, z); break;
                    case 1: gg = gaz_devi_olustur(isim, gun_saat, z); break;
                    case 2: gg = buz_devi_olustur(isim, gun_saat, z); break;
                    case 3: gg = cuce_olustur(isim, gun_saat, z);     break;
                }
                if (gg) simulasyon_gezegen_ekle(sim, gg);
            } else {
                // KISI: isim#yas#omur#arac
                const char* isim      = flds[0];
                int         yas       = atoi(flds[1]);
                double      omur      = atof(flds[2]);
                const char* aracIsim  = flds[3];
                UzayAraci* ar = bul_arac(sim, aracIsim);
                if (ar) {
                    Kisi* k = kisi_olustur(isim, yas, omur, ar);
                    if (k) {
                        simulasyon_kisi_ekle(sim, k);
                        arac_yolcu_ekle(ar, k);
                    }
                }
            }
        }
        else if (alan == 5) {
            // ARAC: isim#cikis#hedef#tarih#kalan_saat
            const char* isim      = flds[0];
            const char* cikisStr  = flds[1];
            const char* hedefStr  = flds[2];
            int g, m, y;
            sscanf(flds[3], "%d.%d.%d", &g, &m, &y);
            Zaman* cz   = zaman_olustur(y, m, g);
            int kalan   = atoi(flds[4]);

            Gezegen* cikis = bul_gezegen(sim, cikisStr);
            Gezegen* hedef = bul_gezegen(sim, hedefStr);
            if (cikis && hedef && cz) {
                UzayAraci* ar = arac_olustur(isim, cikis, hedef, cz, kalan);
                if (ar) {
                    ar->yolcular = calloc(sim->max_kisi, sizeof(Kisi*));
                    if (ar->yolcular) {
                        simulasyon_arac_ekle(sim, ar);
                    } else {
                        printf("Bellek hatasi: Yolcu listesi olusturulamadi\n");
                        arac_yoket(ar);
                    }
                }
            } else if (cz) {
                zaman_yoket(cz);
            }
        }
    }
    fclose(dosya);
}
