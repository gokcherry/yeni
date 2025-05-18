
#include "Simulasyon.h"
#include "DosyaOkuma.h"    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
  #include <windows.h>
  #define sleep_ms(ms) Sleep(ms)
#else
  #include <unistd.h>
  #define sleep_ms(ms) usleep((ms) * 1000)
#endif


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

static void gezegen_saatleri_ilerlet(Simulasyon* sim) {
    for (int i = 0; i < sim->gezegen_sayisi; i++) {
        zaman_ilerlet(&sim->gezegenler[i]->tarih, 1);
    }
}

static void araclari_guncelle(Simulasyon* sim) {
    for (int i = 0; i < sim->arac_sayisi; i++) {
        UzayAraci* a = sim->araclar[i];
        if (a->durum == ARAC_VARDI || a->durum == ARAC_IMHA) 
            continue;

        // Bekliyorsa çıkış zamanına gelince yola çık
        if (a->durum == ARAC_BEKLIYOR &&
            zaman_karsilastir(sim->zaman, a->cikis_tarihi) >= 0) {
            a->durum = ARAC_YOLDA;
        }

        // Yoldaysa kalan süreyi azalt, yolcular öldüyse IMHA
        if (a->durum == ARAC_YOLDA) {
            a->kalan_sure--;
            for (int j = 0; j < a->yolcu_sayisi; j++) {
                if (!a->yolcular[j]->yasiyor) {
                    a->durum = ARAC_IMHA;
                    break;
                }
            }
            // Varış
            if (a->durum == ARAC_YOLDA && a->kalan_sure <= 0) {
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

static bool sim_bitti(Simulasyon* sim) {
    for (int i = 0; i < sim->arac_sayisi; i++) {
        if (sim->araclar[i]->durum == ARAC_BEKLIYOR ||
            sim->araclar[i]->durum == ARAC_YOLDA)
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

    int hours = (a->durum == ARAC_YOLDA ? a->kalan_sure : a->toplam_sure);
    for (int h = 0; h < hours; h++)
        zaman_ilerlet(&temp, 1);
    return zaman_to_string(&temp);
}

static void yazdir(Simulasyon* sim) {
    // Gezegenler
    printf("Gezegenler:\n    ");
    for (int i = 0; i < sim->gezegen_sayisi; i++)
        printf("   --- %s ---", sim->gezegenler[i]->isim);
    printf("\n");

    // Tarihler
    printf("Tarih      ");
    for (int i = 0; i < sim->gezegen_sayisi; i++) {
        Gezegen* g = sim->gezegenler[i];
        printf("   %02d.%02d.%04d",
               g->tarih.gun, g->tarih.ay, g->tarih.yil);
    }
    printf("\n");

    // Nüfuslar
    printf("Nufus      ");
    for (int i = 0; i < sim->gezegen_sayisi; i++) {
        int pop = 0;
        for (int j = 0; j < sim->kisi_sayisi; j++) {
            Kisi* k = sim->kisiler[j];
            if (k->yasiyor && k->bulundugu == sim->gezegenler[i])
                pop++;
        }
        printf("   %3d", pop);
    }
    printf("\n\n");

    // Uzay Araçları
    printf("Uzay Gemileri:\n");
    printf("Arac Adi  Durum     Cikis   Varıs   Kalan Saat   Varıs Tarihi\n");
    for (int i = 0; i < sim->arac_sayisi; i++) {
        UzayAraci* a = sim->araclar[i];
        const char* durum_str =
            a->durum == ARAC_BEKLIYOR ? "Bekliyor" :
            a->durum == ARAC_YOLDA    ? "Yolda"    :
            a->durum == ARAC_VARDI    ? "Vardi"    : "IMHA";
        char* eta = eta_str(a);
        printf("%-8s  %-8s  %-6s  %-6s   %4d      %s\n",
               a->isim,
               durum_str,
               a->cikis->isim,
               a->hedef->isim,
               (a->durum == ARAC_YOLDA ? a->kalan_sure : 0),
               eta);
        free(eta);
    }
    printf("\n");
}

void simulasyon_calistir(Simulasyon* sim) {
    while (!sim_bitti(sim)) {
        ekran_temizle();
        yazdir(sim);

        gezegen_saatleri_ilerlet(sim);
        zaman_ilerlet(sim->zaman, 1);
        araclari_guncelle(sim);

        sleep_ms(100);
    }

    ekran_temizle();
    yazdir(sim);
    printf("SIMULASYON TAMAMLANDI: Tum gemiler hedefe ulasti veya imha oldu.\n");
}
