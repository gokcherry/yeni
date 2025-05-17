#ifndef ZAMAN_H
#define ZAMAN_H

typedef struct {
    int yil, ay, gun, saat;
} Zaman;

Zaman* zaman_yarat(int yil, int ay, int gun);
void    zaman_yoket(Zaman* z);
void    zaman_ilerlet(Zaman* z, int saat_gun);

int     zaman_karsilastir(const Zaman* z1, const Zaman* z2);
void    zaman_arttir     (Zaman* z, int saat_gun);
char*   zaman_to_string  (const Zaman* z);

#endif // ZAMAN_H
