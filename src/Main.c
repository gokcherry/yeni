
#include "Simulasyon.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    const char* gezegen_dosyasi;
    const char* arac_dosyasi;
    const char* kisi_dosyasi;
    int gun_sayisi;

    if (argc == 5) {
        gezegen_dosyasi = argv[1];
        arac_dosyasi    = argv[2];
        kisi_dosyasi    = argv[3];
        gun_sayisi      = atoi(argv[4]);
    }
    else if (argc == 1) {
        gezegen_dosyasi = "data/Gezegenler.txt";
        arac_dosyasi    = "data/Araclar.txt";
        kisi_dosyasi    = "data/Kisiler.txt";
        gun_sayisi      = 365;
    }
    else {
        return EXIT_FAILURE;
    }

    Simulasyon* sim = simulasyon_olustur(10, 10, 100);
    if (!sim) {
        fprintf(stderr, "Error: simulasyon olusturulamadi\n");
        return EXIT_FAILURE;
    }

    simulasyon_gezegen_oku(gezegen_dosyasi, sim);
    simulasyon_arac_oku   (arac_dosyasi, sim);
    simulasyon_kisi_oku   (kisi_dosyasi, sim);

    simulasyon_calistir(sim);
    simulasyon_yoket(sim);

    return EXIT_SUCCESS;
}
