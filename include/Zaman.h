#ifndef ZAMAN_H
#define ZAMAN_H

typedef struct {
    int yil, ay, gun, saat;
} Zaman;

/** Oluşturur (GG.AA.YYYY için yıl, ay, gün) */
Zaman* zaman_olustur(int yil, int ay, int gun);

/** Serbest bırakır */
void   zaman_yoket(Zaman* z);

/**
 * Zamanı saat adım adım ilerletir.
 * @param z      - Zaman objesi
 * @param hours  - Toplam ilerletilecek saat sayısı
 */
void   zaman_ilerlet(Zaman* z, int hours);

/** İki zamanı karşılaştırır (z1 - z2) */
int    zaman_karsilastir(const Zaman* z1, const Zaman* z2);

/** “GG.AA.YYYY SS:00” stringi döner */
char*  zaman_to_string(const Zaman* z);

#endif // ZAMAN_H
