#include "Zaman.h"
#include <stdlib.h>
#include <stdio.h>

static int ay_gun_sayisi(int ay, int yil) {
    switch (ay) {
      case 1: case 3: case 5: case 7:
      case 8: case 10: case 12: return 31;
      case 4: case 6: case 9: case 11: return 30;
      case 2:
        return ((yil%4==0 && yil%100!=0) || (yil%400==0)) ? 29 : 28;
      default: return 30;
    }
}

Zaman* zaman_olustur(int yil, int ay, int gun) {
    Zaman* z = malloc(sizeof(Zaman));
    if (!z) return NULL;
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
    if (z1->yil  != z2->yil)  return z1->yil  - z2->yil;
    if (z1->ay   != z2->ay )  return z1->ay   - z2->ay;
    if (z1->gun  != z2->gun)  return z1->gun  - z2->gun;
    return z1->saat - z2->saat;
}

static void _arttir_bir_saat(Zaman* z) {
    z->saat++;
    if (z->saat >= 24) {           // Evrensel saat birimi: 24
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

void zaman_ilerlet(Zaman* z, int hours) {
    for (int i = 0; i < hours; i++) {
        _arttir_bir_saat(z);
    }
}

char* zaman_to_string(const Zaman* z) {
    char* buf = malloc(20);
    if (!buf) return NULL;
    snprintf(buf, 20, "%02d.%02d.%04d %02d:00",
             z->gun, z->ay, z->yil, z->saat);
    return buf;
}
