/**
*
* @author Gökçe Çiçek Yağmur - gokce.yagmur@ogr.sakarya.edu.tr
* @since Mayıs 2025
* <p>
* Zaman yapısı ve fonksiyonları
* </p>
*/
#include <stdlib.h>
#include <stdio.h>
#include "Zaman.h"

//Takvimdeki aylara göre hazırlandım.
static int ay_gun_sayisi(int ay, int yil) {
    switch (ay) {
        case 1: case 3: case 5: case 7:
        case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return (((yil % 4 == 0 && yil % 100 != 0) || (yil % 400 == 0)) ? 29 : 28);
        default: return 30;
    }
}

Zaman* zaman_olustur(int yil, int ay, int gun) {
    Zaman* z = malloc(sizeof(Zaman));
    z->yil  = yil;
    z->ay   = ay;
    z->gun  = gun;
    z->saat = 0;
    return z;
}

void zaman_yoket(Zaman* z) {
    free(z);
}

int zaman_karsilastir(const Zaman* z1, const Zaman* z2) {
    if (z1->yil != z2->yil) return z1->yil - z2->yil;
    if (z1->ay  != z2->ay)  return z1->ay  - z2->ay;
    if (z1->gun != z2->gun) return z1->gun - z2->gun;
    return z1->saat - z2->saat;
}

void zaman_ilerlet(Zaman* z, int hours) {
    for (int i = 0; i < hours; i++) {
        z->saat++;
        if (z->saat >= 24) {
            z->saat = 0;
            z->gun++;
            if (z->gun > ay_gun_sayisi(z->ay, z->yil)) {
                z->gun = 1;
                z->ay++;
                if (z->ay > 12) {
                    z->ay = 1;
                    z->yil++;
                }
            }
        }
    }
}

char* zaman_to_string(const Zaman* z) {
    char* buf = malloc(20);
    snprintf(buf, 20, "%02d.%02d.%04d %02d:00", z->gun, z->ay, z->yil, z->saat);
    return buf;
}
