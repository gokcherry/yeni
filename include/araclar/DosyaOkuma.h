#ifndef DOSYA_OKUMA_H
#define DOSYA_OKUMA_H

#include <stdio.h>
#include "../modeller/Kisi.h"
#include "../modeller/Gezegen.h"
#include "../modeller/UzayGemisi.h"
#include "../simulasyon/Simulasyon.h"

void veri_oku(const char* dosya_yolu, Simulasyon* sim);

#endif // DOSYA_OKUMA_H