/** 
* @file KonsolArayuz.hpp
* @description Konsol ekranın tamponunu yöneten ve kullanıcının etkileşim sağlayacağı menülerin çizilmesini sağlayacak arayüz sınıfı başlık dosyası.
* @course 1.Öğretim A Grubu
* @assignment 1.Ödev
* @date 15.11.2026 (22.11.2026 son güncelleme) 
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#ifndef KONSOLARAYUZ_HPP
#define KONSOLARAYUZ_HPP

#include "BagliListe.hpp"

class KonsolArayuz {
private:
    BagliListe* liste;
    char** ekran;
    int ekranSatir;
    int ekranSutun;


    void ekranHazirla(int satir, int sutun);
    void ekranTemizle();
    void ekranSil();
    void metinYaz(int x, int y, const char* metin);
    void sayiYaz(int x, int y, int sayi);


    void kutuCiz(MatrisDugumu* dugum, int y, bool seciliMi);
    void normalMatrisCiz(Matris* matris, int basX, int basY);
    void satirSilmeMatrisCiz(Matris* matris, int basX, int basY, int seciliSatir);
    void sutunSilmeMatrisCiz(Matris* matris, int basX, int basY, int seciliSutun);

    void anaMenuCiz(int menuX);
    void islemMenuCiz(int menuX);
    void satirSilMenuCiz(int menuX);
    void sutunSilMenuCiz(int menuX);

    void ciz(int mod, int altSecim);
    void islemMenusu();
    void satirSilMenusu();
    void sutunSilMenusu();
    void satirSutunDegistirMenusu();

public:

    KonsolArayuz(BagliListe* liste);
    ~KonsolArayuz();

    void calistir();
};

#endif