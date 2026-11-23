/** 
* @file Matris.hpp
* @description Satır düğümlerini bağlı liste olarak tutan ve boyut ortalama vb bilgilerin saklandığı matrisi sınıfının tanımının başlık dosyası.
* @assignment 1.Ödev
* @date 15.11.2026 (22.11.2026 son güncelleme)
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#ifndef MATRIS_HPP
#define MATRIS_HPP

#include "SatirDugumu.hpp"

class Matris {
private:
    SatirDugumu* ilkSatir;
    SatirDugumu* sonSatir;
    int satirSayisi;
    int sutunSayisi;
    double ortalama;

public:
    Matris();
    ~Matris();

    void satirEkle(SatirDugumu* yeniSatir);
    void rastgeleOlustur();
    bool satirSil(int satirIndeks);
    bool sutunSil(int sutunIndeks);
    bool satirSutunDegistir(int satirIndeks, int sutunIndeks);
    void ortalamaHesapla();


    SatirDugumu* satirGetir(int satirIndeks) const;
    int degerGetir(int satirIndeks, int sutunIndeks) const;
    bool bosMu() const;
    bool kareMi() const;


    SatirDugumu* getIlkSatir() const;
    int getSatirSayisi() const;
    int getSutunSayisi() const;
    void setSutunSayisi(int sutunSayisi);
    double getOrtalama() const;
};

#endif