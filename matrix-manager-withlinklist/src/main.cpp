/** 
* @file main.cpp
* @description Dosyayı yükleyip konsol arayüzünü başlatıp programı çalıştırır ve çıkışta bellek temizleme işlemini yapar.
* @course 1.Öğretim A Grubu
* @assignment 1.Ödev
* @date 16.11.2026
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#include "BagliListe.hpp"
#include "KonsolArayuz.hpp"
#include <cstdlib>
#include <ctime>

int main() {
    srand((unsigned int)time(nullptr));

    BagliListe* liste = new BagliListe();
    liste->dosyadanOku("kayitlar.txt");

    KonsolArayuz* arayuz = new KonsolArayuz(liste);
    arayuz->calistir();

    delete arayuz;
    delete liste;

    return 0;
}