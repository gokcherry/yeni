#ifndef GEZEGEN_H
#define GEZEGEN_H

#include "ForwardDefs.h"

typedef enum {
    KAYAC,
    GAZ_DEVI,
    BUZ_DEVI,
    CUCE
} GezegenTipi;

typedef struct Gezegen {
    char* isim;
    GezegenTipi tip;
    double sicaklik_gucu;
    double zehirlilik;
} Gezegen;

Gezegen* gezegen_yarat(const char* isim, GezegenTipi tip, double sicaklik_gucu, double zehirlilik);
void gezegen_yoket(Gezegen* g);

#endif // GEZEGEN_H