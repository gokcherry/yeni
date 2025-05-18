/**
*
* @author Gökçe Çiçek Yağmur - gokce.yagmur@ogr.sakarya.edu.tr
* @since Mayıs 2025
* <p>
* Zaman header dosyası. Zaman yapısı ve fonksiyonları burada tanımlanır.
* </p>
*/
#ifndef ZAMAN_H
#define ZAMAN_H

typedef struct {
    int yil;
    int ay;
    int gun;
    int saat;
} Zaman;

Zaman* zaman_olustur(int yil, int ay, int gun);
void   zaman_yoket(Zaman* z);
int    zaman_karsilastir(const Zaman* z1, const Zaman* z2);
void   zaman_ilerlet(Zaman* z, int hours);
char*  zaman_to_string(const Zaman* z);

#endif
