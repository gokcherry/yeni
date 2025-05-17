#include "simulasyon/Simulasyon.h"
#include "modeller/Zaman.h"
#include "modeller/Gezegen.h"
#include "modeller/Kisi.h"
#include "modeller/UzayGemisi.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>

static int bitis_kontrol(const Simulasyon* s) {
    for (int i = 0; i < s->veri->arac_say; i++) {
        UzayAraci* a = s->veri->araclar[i];
        if (!a->imha && (a->yolda || a->kalan_sure > 0)) 
            return 0;
    }
    return 1;
}

// Gezegen ve araç durumunu ekrana basan yardımcı fonksiyon
static void durum_yazdir(const Simulasyon* s) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    // Gezegenler
    printf("Gezegenler:\n            ");
    for (int i = 0; i < s->veri->gezegen_say; i++)
        printf("  --- %-3s ---", s->veri->gezegenler[i]->isim);
    printf("\nTarih       ");
    for (int i = 0; i < s->veri->gezegen_say; i++) {
        char* ts = zaman_to_string(&s->veri->gezegenler[i]->tarih);
        printf(" %-16s", ts);
        free(ts);
    }
    printf("\nNüfus       ");
    for (int i = 0; i < s->veri->gezegen_say; i++)
        printf(" %-16d", s->veri->gezegenler[i]->nufus);
    printf("\n\n");

    // Uzay Araçları
    printf("Uzay Araçları:\n");
    printf("%-10s %-10s %-6s %-6s %-20s %s\n",
        "Araç Adı","Durum","Çıkış","Varış","Hedefe Kalan Saat","Hedefe Varacağı Tarih");
    for (int i = 0; i < s->veri->arac_say; i++) {
        UzayAraci* a = s->veri->araclar[i];
        const char* durum;
        if (a->imha) {
            durum = "İMHA";
        } else if (a->yolda) {
            durum = "YOLDA";
        } else {
            // Henüz kalkış zamanı gelmediyse
            if (zaman_karsilastir(&a->cikis->tarih, &a->cikis_tarihi) < 0)
                durum = "Bekliyor";
            else
                durum = "Vardı";
        }

        char vt[11];
        if (a->imha)
            strcpy(vt, "--");
        else
            sprintf(vt, "%02d.%02d.%04d",
                a->varis->tarih.gun, a->varis->tarih.ay, a->varis->tarih.yil);

        printf("%-10s %-10s %-6s %-6s %-20.0f %s\n",
            a->isim, durum,
            a->cikis->isim, a->varis->isim,
            a->kalan_sure, vt);
    }
}

Simulasyon* simulasyon_yarat(Veri* v) {
    Simulasyon* s = malloc(sizeof(Simulasyon));
    s->veri = v;
    // Başlangıç nüfus ataması
    for (int i = 0; i < v->kisi_say; i++) {
        Kisi* k = v->kisiler[i];
        if (k->yasiyor && !k->arac->yolda)
            k->arac->cikis->nufus++;
    }
    return s;
}

void simulasyon_calistir(Simulasyon* s) {
    // Döngü; bitmeyene kadar iterasyon başına 1 saat
    while (!bitis_kontrol(s)) {
        // Gezegen saatlerini ilerlet
        for (int i = 0; i < s->veri->gezegen_say; i++) {
            Gezegen* g = s->veri->gezegenler[i];
            zaman_arttir(&g->tarih, g->saat_gun);
        }
        // Araçları güncelle (kalkış ve varış)
        for (int i = 0; i < s->veri->arac_say; i++) {
            UzayAraci* a = s->veri->araclar[i];
            if (!a->yolda && !a->imha
                && zaman_karsilastir(&a->cikis->tarih, &a->cikis_tarihi) == 0) {
                a->yolda = 1;
                a->cikis->nufus -= a->yolcu_say;
            }
            arac_guncelle(a);
        }
        // Kişi yaşlanma ve ölüm kontrolleri
        for (int i = 0; i < s->veri->kisi_say; i++) {
            Kisi* k = s->veri->kisiler[i];
            if (!k->yasiyor) continue;
            double f = k->arac->yolda ? 1.0 : k->arac->cikis->yaslanma_katsayisi;
            kisi_yaslandir(k, f);
            if (!k->yasiyor) {
                if (!k->arac->yolda)
                    k->arac->cikis->nufus--;
                int hayatta = 0;
                for (int j = 0; j < k->arac->yolcu_say; j++)
                    if (k->arac->yolcular[j]->yasiyor) hayatta++;
                if (!hayatta)
                    k->arac->imha = 1;
            }
        }
        // Güncel durumu yazdır
        durum_yazdir(s);
    }

    // Son durum raporu
    durum_yazdir(s);
}

void simulasyon_yok_et(Simulasyon* s) {
    free(s);
}
