#include "../../include/modeller/UzayGemisi.h"
#include <stdlib.h>
#include <string.h>


UzayAraci* arac_yarat(const char* isim, AracTipi tip, int max_yolcu, double yakit, Gezegen* hedef) {
    UzayAraci* a = (UzayAraci*)malloc(sizeof(UzayAraci));
    if (a == NULL) return NULL;
    
    a->isim = strdup(isim);
    a->tip = tip;
    a->max_yolcu = max_yolcu;
    a->yolcu_sayisi = 0;
    a->yakit = yakit;
    a->hedef = hedef;
    
    // Yolcu dizisi için bellek ayır
    a->yolcular = (Kisi**)malloc(sizeof(Kisi*) * max_yolcu);
    if (a->yolcular == NULL) {
        free(a->isim);
        free(a);
        return NULL;
    }
    
    // Yolcu dizisini başlangıçta NULL ile doldur
    for (int i = 0; i < max_yolcu; i++) {
        a->yolcular[i] = NULL;
    }
    
    return a;
}

void arac_yoket(UzayAraci* a) {
    if (a) {
        free(a->isim);
        if (a->yolcular) {
            free(a->yolcular);
        }
        free(a);
    }
}

void arac_yolcu_ekle(UzayAraci* a, Kisi* k) {
    if (!a || !k || a->yolcu_sayisi >= a->max_yolcu) return;
    
    // Boş bir slot ara
    for (int i = 0; i < a->max_yolcu; i++) {
        if (a->yolcular[i] == NULL) {
            a->yolcular[i] = k;
            a->yolcu_sayisi++;
            break;
        }
    }
}

int arac_yolcu_cikar(UzayAraci* a, Kisi* k) {
    if (!a || !k) return 0;
    
    for (int i = 0; i < a->max_yolcu; i++) {
        if (a->yolcular[i] == k) {
            a->yolcular[i] = NULL;
            a->yolcu_sayisi--;
            return 1;
        }
    }
    
    return 0;
}

void arac_hedef_guncelle(UzayAraci* a, Gezegen* g) {
    if (a) {
        a->hedef = g;
    }
}