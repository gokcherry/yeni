/**
*
* @author Gökçe Çiçek Yağmur - gokce.yagmur@ogr.sakarya.edu.tr
* @since Mayıs 2025
* <p>
* Simülasyon yapısı ve fonksiyonları. Simülasyon, gezegenlerin, araçların ve kişilerin durumunu tutar. 
* </p>
*/
#include "Simulasyon.h"
#include "DosyaOkuma.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//uyutma fonksiyonu
#ifdef _WIN32
  #include <windows.h>
  #define sleep_ms(ms) Sleep(ms)
#else
  #include <unistd.h>
  #define sleep_ms(ms) usleep((ms) * 1000)
#endif

// Ayın gün sayısını, gezegenin takvimine göre hesaplar
static int ay_gun_sayisi_planet(int ay, int yil) {
    switch (ay) {
      case 1: case 3: case 5: case 7:
      case 8: case 10: case 12: return 31;
      case 4: case 6: case 9: case 11: return 30;
      case 2:
        return ((yil % 4 == 0 && yil % 100 != 0) || (yil % 400 == 0)) ? 29 : 28;
      default: return 30;
    }
}

// Gezegenin kendi gun_saat değerine göre saatleri ve günleri ilerletir
static void gezegen_zaman_ilerlet(Gezegen* g, int hours) {
    for (int i = 0; i < hours; i++) {
        g->tarih.saat++;
        if (g->tarih.saat >= g->gun_saat) {
            g->tarih.saat = 0;
            g->tarih.gun++;
            if (g->tarih.gun > ay_gun_sayisi_planet(g->tarih.ay, g->tarih.yil)) {
                g->tarih.gun = 1;
                g->tarih.ay++;
                if (g->tarih.ay > 12) {
                    g->tarih.ay = 1;
                    g->tarih.yil++;
                }
            }
        }
    }
}

// Tüm gezegenlerde 1 saatlik adımı uygular
static void gezegen_saatleri_ilerlet(Simulasyon* sim) {
    for (int i = 0; i < sim->gezegen_sayisi; i++) {
        gezegen_zaman_ilerlet(sim->gezegenler[i], 1);
    }
}

// Gezegende veya gemideki her kişiyi yaşlanma katsayısına göre azaltır
static void kisileri_yaslan(Simulasyon* sim) {
    for (int i = 0; i < sim->kisi_sayisi; i++) {
        Kisi* k = sim->kisiler[i];
        if (!k->yasiyor) continue;
        double faktor = 1.0;
        if (k->arac == NULL && k->bulundugu != NULL) {
            // Gezegende yaşıyor
            faktor = k->bulundugu->yaslanma_katsayisi;
        }
        k->kalan_omur -= faktor;
        if (k->kalan_omur <= 0) {
            k->yasiyor = 0;
        }
    }
}

Simulasyon* simulasyon_olustur(int max_gezegen,
                               int max_arac,
                               int max_kisi) {
    Simulasyon* sim = calloc(1, sizeof(Simulasyon));
    if (!sim) return NULL;
    sim->zaman = zaman_olustur(2150, 1, 1);

    sim->max_gezegen    = max_gezegen;
    sim->gezegen_sayisi = 0;
    sim->gezegenler     = malloc(sizeof(Gezegen*) * max_gezegen);

    sim->max_arac       = max_arac;
    sim->arac_sayisi    = 0;
    sim->araclar        = malloc(sizeof(UzayAraci*) * max_arac);

    sim->max_kisi       = max_kisi;
    sim->kisi_sayisi    = 0;
    sim->kisiler        = malloc(sizeof(Kisi*) * max_kisi);

    return sim;
}

void simulasyon_yoket(Simulasyon* sim) {
    if (!sim) return;
    for (int i = 0; i < sim->gezegen_sayisi; i++)
        gezegen_yoket(sim->gezegenler[i]);
    free(sim->gezegenler);

    for (int i = 0; i < sim->arac_sayisi; i++)
        arac_yoket(sim->araclar[i]);
    free(sim->araclar);

    for (int i = 0; i < sim->kisi_sayisi; i++)
        kisi_yoket(sim->kisiler[i]);
    free(sim->kisiler);

    zaman_yoket(sim->zaman);
    free(sim);
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

void simulasyon_gezegen_oku(const char* path, Simulasyon* sim) {
    veri_oku(path, sim);
}

void simulasyon_arac_oku(const char* path, Simulasyon* sim) {
    veri_oku(path, sim);
}

void simulasyon_kisi_oku(const char* path, Simulasyon* sim) {
    veri_oku(path, sim);
}

static void ekran_temizle() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[H\033[J");
#endif
}

static bool sim_bitti(Simulasyon* sim) {
    for (int i = 0; i < sim->arac_sayisi; i++) {
        AracDurum d = sim->araclar[i]->durum;
        if (d == ARAC_BEKLIYOR || d == ARAC_YOLDA)
            return false;
    }
    return true;
}

static char* eta_str(UzayAraci* a) {
    if (a->durum == ARAC_IMHA) return strdup("--");
    Zaman temp = a->hedef->tarih;
    if (a->durum == ARAC_VARDI) {
        return zaman_to_string(&temp);
    }
    // Rotadaki saatleri gezegenin gun_saatine göre ilerletir
    int hours = (a->durum == ARAC_YOLDA ? a->kalan_sure : a->toplam_sure);
    for (int h = 0; h < hours; h++) {
        temp.saat++;
        if (temp.saat >= a->hedef->gun_saat) {
            temp.saat = 0;
            temp.gun++;
            if (temp.gun > ay_gun_sayisi_planet(temp.ay, temp.yil)) {
                temp.gun = 1;
                temp.ay++;
                if (temp.ay > 12) {
                    temp.ay = 1;
                    temp.yil++;
                }
            }
        }
    }
    return zaman_to_string(&temp);
}

static void yazdir(Simulasyon* sim) {
    // Gezegenler
    printf("    Gezegenler:\n");
    printf("\t");
    printf("\t");
    for (int i = 0; i < sim->gezegen_sayisi; i++) {
        printf("%-14s", sim->gezegenler[i]->isim);
    }
    printf("\n");
    printf("\n    Tarih      ");
    for (int i = 0; i < sim->gezegen_sayisi; i++) {
        Gezegen* g = sim->gezegenler[i];
        char buf[16];
        snprintf(buf, sizeof(buf), "%02d.%02d.%04d",
                 g->tarih.gun, g->tarih.ay, g->tarih.yil);
        printf("%-14s", buf);
    }
    printf("\n    Nufus      ");
    for (int i = 0; i < sim->gezegen_sayisi; i++) {
        int pop = 0;
        for (int j = 0; j < sim->kisi_sayisi; j++) {
            Kisi* k = sim->kisiler[j];
            if (k->yasiyor && k->bulundugu == sim->gezegenler[i])
                pop++;
        }
        printf("%-14d", pop);
    }
    printf("\n\n");


    printf("    Uzay Araclari:\n");

    printf("    %-10s %-10s %-10s %-10s %-18s %-20s\n",
           "Arac Adi", "Durum", "Cikis", "Varis",
           "Hedefe Kalan Saat", "Hedefe Varis Tarih");
    // Alt çizgi
    printf("    %.*s\n", 10+1+10+1+10+1+10+1+18+1+20);

    // Veriler
    for (int i = 0; i < sim->arac_sayisi; i++) {
        UzayAraci* a = sim->araclar[i];
        const char* durum = a->durum == ARAC_BEKLIYOR ? "Bekliyor" :
                            a->durum == ARAC_YOLDA    ? "Yolda"    :
                            a->durum == ARAC_VARDI    ? "Vardi"    : "IMHA";
        char* eta = eta_str(a);
        printf("    %-10s %-10s %-10s %-10s %-18d %-20s\n",
               a->isim,
               durum,
               a->cikis->isim,
               a->hedef->isim,
               (a->durum == ARAC_YOLDA ? a->kalan_sure : 0),
               eta);
        free(eta);
    }
    printf("\n");
}

static void araclari_guncelle(Simulasyon* sim) {
    for (int i = 0; i < sim->arac_sayisi; i++) {
        UzayAraci* a = sim->araclar[i];
        if (a->durum == ARAC_VARDI || a->durum == ARAC_IMHA) 
            continue;
        if (a->durum == ARAC_BEKLIYOR &&
            zaman_karsilastir(sim->zaman, a->cikis_tarihi) >= 0) {
            a->durum = ARAC_YOLDA;
        }
        if (a->durum == ARAC_YOLDA) {
            a->kalan_sure--;
            bool all_dead = true;
            for (int j = 0; j < a->yolcu_sayisi; j++) {
                if (a->yolcular[j]->yasiyor) {
                    all_dead = false;
                    break;
                }
            }
            if (all_dead && a->yolcu_sayisi > 0) {
                a->durum = ARAC_IMHA;
                continue;
            }
            if (a->kalan_sure <= 0) {
                a->durum = ARAC_VARDI;
                for (int j = 0; j < a->yolcu_sayisi; j++) {
                    Kisi* k = a->yolcular[j];
                    k->arac      = NULL;
                    k->bulundugu = a->hedef;
                }
            }
        }
    }
}

// Simulasyonun bitip bitmediğini kontrol eder.     ekranı temizler.
void simulasyon_calistir(Simulasyon* sim) {
    while (!sim_bitti(sim)) {
        ekran_temizle();
        yazdir(sim);

        gezegen_saatleri_ilerlet(sim);   
        zaman_ilerlet(sim->zaman, 1);   
        kisileri_yaslan(sim);            
        araclari_guncelle(sim);         

        sleep_ms(100);
    }
    ekran_temizle();
    yazdir(sim);
    printf("SIMULASYON TAMAMLANDI: Tum gemiler hedefe ulasti veya imha oldu.\n");
}
