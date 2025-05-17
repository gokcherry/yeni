#include "Simulasyon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Gezegeni isimle bulur
static Gezegen* bul_gezegen(Simulasyon* sim, const char* isim) {
    for (int i = 0; i < sim->gezegen_sayisi; i++) {
        if (strcmp(sim->gezegenler[i]->isim, isim) == 0)
            return sim->gezegenler[i];
    }
    return NULL;
}

// Aracı isimle bulur
static UzayAraci* bul_arac(Simulasyon* sim, const char* isim) {
    for (int i = 0; i < sim->arac_sayisi; i++) {
        if (strcmp(sim->araclar[i]->isim, isim) == 0)
            return sim->araclar[i];
    }
    return NULL;
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


Simulasyon* simulasyon_olustur(int max_gezegen,
                               int max_arac,
                               int max_kisi) {
    Simulasyon* sim = calloc(1, sizeof(Simulasyon));
    if (!sim) return NULL;

    sim->zaman         = zaman_olustur(2150, 1, 1);

    sim->max_gezegen   = max_gezegen;
    sim->gezegen_sayisi= 0;
    sim->gezegenler    = malloc(sizeof(Gezegen*) * max_gezegen);

    sim->max_arac      = max_arac;
    sim->arac_sayisi   = 0;
    sim->araclar       = malloc(sizeof(UzayAraci*) * max_arac);

    sim->max_kisi      = max_kisi;
    sim->kisi_sayisi   = 0;
    sim->kisiler       = malloc(sizeof(Kisi*) * max_kisi);

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

void simulasyon_gezegen_oku(const char* path, Simulasyon* sim) {
    FILE* f = fopen(path, "r");
    if (!f) return;
    char buf[256];
    while (fgets(buf, sizeof(buf), f)) {
        buf[strcspn(buf, "\r\n")] = '\0';
        if (!buf[0]) continue;

        char* isim    = strtok(buf, "#");
        char* tip_s   = strtok(NULL, "#");
        char* saat_s  = strtok(NULL, "#");
        char* tarih_s = strtok(NULL, "#");
        if (!isim || !tip_s || !saat_s || !tarih_s) continue;

        int tip      = atoi(tip_s);
        int gun_saat = atoi(saat_s);
        int g, a, y;
        sscanf(tarih_s, "%d.%d.%d", &g, &a, &y);
        Zaman z = { .yil = y, .ay = a, .gun = g, .saat = 0 };

        Gezegen* gg = NULL;
        switch (tip) {
            case 0: gg = kayac_gezegen_olustur(isim, gun_saat, z); break;
            case 1: gg = gaz_devi_olustur(isim, gun_saat, z); break;
            case 2: gg = buz_devi_olustur(isim, gun_saat, z); break;
            case 3: gg = cuce_olustur(isim, gun_saat, z);     break;
        }
        if (gg) simulasyon_gezegen_ekle(sim, gg);
    }
    fclose(f);
}

void simulasyon_arac_oku(const char* path, Simulasyon* sim) {
    FILE* f = fopen(path, "r");
    if (!f) return;
    char buf[256];
    while (fgets(buf, sizeof(buf), f)) {
        buf[strcspn(buf, "\r\n")] = '\0';
        if (!buf[0]) continue;

        char* isim = strtok(buf, "#");
        char* cis  = strtok(NULL, "#");
        char* hedf = strtok(NULL, "#");
        char* trs  = strtok(NULL, "#");
        char* sstr = strtok(NULL, "#");
        if (!isim || !cis || !hedf || !trs || !sstr) continue;

        Gezegen* cikis = bul_gezegen(sim, cis);
        Gezegen* hedef = bul_gezegen(sim, hedf);
        int g, m, y;
        sscanf(trs, "%d.%d.%d", &g, &m, &y);
        Zaman* cz = zaman_olustur(y, m, g);
        int kalan = atoi(sstr);

        if (cikis && hedef) {
            UzayAraci* ar = arac_olustur(isim, cikis, hedef, cz, kalan);
            ar->yolcular  = calloc(sim->max_kisi, sizeof(Kisi*));
            simulasyon_arac_ekle(sim, ar);
        } else {
            zaman_yoket(cz);
        }
    }
    fclose(f);
}

void simulasyon_kisi_oku(const char* path, Simulasyon* sim) {
    FILE* f = fopen(path, "r");
    if (!f) return;
    char buf[256];
    while (fgets(buf, sizeof(buf), f)) {
        buf[strcspn(buf, "\r\n")] = '\0';
        if (!buf[0]) continue;

        char* isim = strtok(buf, "#");
        char* ys   = strtok(NULL, "#");
        char* os   = strtok(NULL, "#");
        char* arnm = strtok(NULL, "#");
        if (!isim || !ys || !os || !arnm) continue;

        int yas     = atoi(ys);
        double omur = atof(os);
        UzayAraci* ar = bul_arac(sim, arnm);
        if (!ar) continue;

        Kisi* k = kisi_olustur(isim, yas, omur, ar);
        simulasyon_kisi_ekle(sim, k);
        arac_yolcu_ekle(ar, k);
    }
    fclose(f);
}
void simulasyon_calistir(Simulasyon* sim,
                         int gun_sayisi,
                         FILE* out) {
    // Günlük sim: her biri 24 saat
    for (int d = 1; d <= gun_sayisi; d++) {
        // 1 gün = 24 saat ilerlet
        zaman_ilerlet(sim->zaman, 24);

        // Araçların kalan sürelerini azalt, varışta indir
        for (int i = 0; i < sim->arac_sayisi; i++) {
            UzayAraci* a = sim->araclar[i];
            if (a->kalan_sure > 0) {
                a->kalan_sure -= 24;
                if (a->kalan_sure <= 0) {
                    // Varış
                    for (int j = 0; j < a->yolcu_sayisi; j++) {
                        Kisi* k = a->yolcular[j];
                        k->arac      = NULL;
                        k->bulundugu = a->hedef;
                    }
                    a->yolcu_sayisi = 0;
                }
            }
        }

        // Kişileri yaşlandır
        for (int i = 0; i < sim->kisi_sayisi; i++) {
            Kisi* k = sim->kisiler[i];
            if (!k->yasiyor) continue;

            double aged_hours;
            if (k->arac) {
                // hâlâ uzayda → normal 24 saat/gün
                aged_hours = 24.0;
            } else if (k->bulundugu) {
                // bulunduğu gezegenin gün uzunluğu × katsayısı
                aged_hours = k->bulundugu->gun_saat
                           * k->bulundugu->yaslanma_katsayisi;
            } else {
                aged_hours = 0;
            }

            k->kalan_omur -= aged_hours;
            if (k->kalan_omur <= 0) {
                k->yasiyor = 0;
            }
        }
    }

    // ——— Çıktı: Gezegenler ———
    fprintf(out, "Gezegenler:\n");
    // Başlık satırı
    fprintf(out, "%-12s", "");
    for (int i = 0; i < sim->gezegen_sayisi; i++)
        fprintf(out, "    --- %s ---", sim->gezegenler[i]->isim);
    fprintf(out, "\n");

    // Tarih satırı
    fprintf(out, "%-12s", "Tarih");
    for (int i = 0; i < sim->gezegen_sayisi; i++) {
        Gezegen* g = sim->gezegenler[i];
        fprintf(out, "   %02d.%02d.%04d",
                g->tarih.gun, g->tarih.ay, g->tarih.yil);
    }
    fprintf(out, "\n");

    // Nüfus satırı
    fprintf(out, "%-12s", "Nüfus");
    for (int i = 0; i < sim->gezegen_sayisi; i++) {
        int pop = 0;
        for (int j = 0; j < sim->kisi_sayisi; j++) {
            Kisi* k = sim->kisiler[j];
            if (k->yasiyor && k->bulundugu == sim->gezegenler[i])
                pop++;
        }
        fprintf(out, "   %3d", pop);
    }
    fprintf(out, "\n\n");

    // ——— Çıktı: Uzay Araçları ———
    fprintf(out, "Uzay Araçları:\n");
    fprintf(out, "%-8s %-8s %-8s %-8s %-10s %s\n",
            "Araç", "Durum", "Çıkış", "Varış", "Kalan Saat", "Varış Tarih");

    for (int i = 0; i < sim->arac_sayisi; i++) {
        UzayAraci* a = sim->araclar[i];
        const char* durum = a->kalan_sure > 0
                            ? "Yolda"
                            : (a->kalan_sure == 0 && a->yolcu_sayisi==0)
                              ? "Vardı"
                              : "Bekliyor";

        // Varış tarihi: şimdi + ceil(kalan_sure/24) gün
        Zaman eta = *sim->zaman;
        if (a->kalan_sure > 0) {
            int extra_days = (a->kalan_sure + 23) / 24;
            for (int d = 0; d < extra_days; d++)
                zaman_ilerlet(&eta, 24);
        }
        char* eta_s = zaman_to_string(&eta);

        fprintf(out, "%-8s %-8s %-8s %-8s %5d     %s\n",
               a->isim,
               durum,
               a->cikis->isim,
               a->hedef->isim,
               a->kalan_sure > 0 ? a->kalan_sure : 0,
               eta_s);

        free(eta_s);
    }
}
