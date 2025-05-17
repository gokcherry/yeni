#include "Simulasyon.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage: %s <gezegen_dosyasi> <arac_dosyasi> <kisi_dosyasi> <gun_sayisi>\n",
               argv[0]);
        return EXIT_FAILURE;
    }

    /* Simülasyonu oluştur */
    Simulasyon* sim = simulasyon_olustur(
        /* max gezegen */ 10,
        /* max arac   */ 10,
        /* max kisi   */ 100
    );
    if (!sim) {
        fprintf(stderr, "Error: simulasyon olusturulamadi\n");
        return EXIT_FAILURE;
    }

    /* Girdi dosyalarından verileri oku */
   // sabit dosya yolları kullanmak istersek:
    simulasyon_gezegen_oku("data/Gezegenler.txt", sim);
    simulasyon_arac_oku   ("data/Araclar.txt",   sim);
    simulasyon_kisi_oku   ("data/Kisiler.txt",   sim);


    /* Çıktı dosyasını aç */
    FILE* out = fopen("simulasyon_sonuc.txt", "w");
    if (!out) {
        perror("Error opening output file");
        simulasyon_yoket(sim);
        return EXIT_FAILURE;
    }

    /* Simülasyonu çalıştır */
    simulasyon_calistir(sim, atoi(argv[4]), out);

    /* Kaynakları temizle */
    fclose(out);
    simulasyon_yoket(sim);

    printf("Simulation completed. Results are in 'simulasyon_sonuc.txt'.\n");
    return EXIT_SUCCESS;
}
