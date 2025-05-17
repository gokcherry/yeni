#include "../include/simulasyon/Simulasyon.h"
#include "../include/araclar/DosyaOkuma.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    // Parametreleri kontrol et
    if (argc != 3) {
        printf("Kullanım: %s <giris_dosyasi> <gun_sayisi>\n", argv[0]);
        return 1;
    }
    
    const char* giris_dosyasi = argv[1];
    int gun_sayisi = atoi(argv[2]);
    
    // Geçerli gün sayısı kontrolü
    if (gun_sayisi <= 0) {
        printf("Hata: Gün sayısı pozitif bir tamsayı olmalıdır.\n");
        return 1;
    }
    
    // Simulasyonu oluştur
    Simulasyon* sim = simulasyon_yarat(100, 50, 200);
    if (!sim) {
        printf("Hata: Simulasyon oluşturulamadı.\n");
        return 1;
    }
    
    // Giriş dosyasından verileri oku
    veri_oku(giris_dosyasi, sim);
    
    // Çıktı dosyasını aç
    FILE* cikti_dosyasi = fopen("simulasyon_sonuc.txt", "w");
    if (!cikti_dosyasi) {
        printf("Hata: Çıktı dosyası oluşturulamadı.\n");
        simulasyon_yoket(sim);
        return 1;
    }
    
    // Simulasyonu çalıştır
    simulasyon_calistir(sim, gun_sayisi, cikti_dosyasi);
    
    // Kaynakları temizle
    fclose(cikti_dosyasi);
    simulasyon_yoket(sim);
    
    printf("Simulasyon tamamlandı. Sonuçlar 'simulasyon_sonuc.txt' dosyasında.\n");
    
    return 0;
}