/** 
* @file SatirDugumu.hpp
* @description Matrisdeki satırları ve o satırdaki sayı düğümlerini yöneten sınıfın tanımı.
* @assignment 1.Ödev
* @date 15.11.2026 (22.11.2026 son güncelleme)
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#ifndef SATIRDUGUMU_HPP
#define SATIRDUGUMU_HPP

#include "SayiDugumu.hpp"

class SatirDugumu {
private:
    SayiDugumu* ilkHucre;
    SatirDugumu* sonrakiSatir;

public:
    SatirDugumu();
    ~SatirDugumu();


    void hucreEkle(int veri);
    bool sutunSil(int sutunIndeks);
    SayiDugumu* hucreGetir(int sutunIndeks) const;


    SayiDugumu* getIlkHucre() const;
    SatirDugumu* getSonrakiSatir() const;
    void setSonrakiSatir(SatirDugumu* sonrakiSatir);
};

#endif
