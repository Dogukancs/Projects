/** 
* @file SatirDugumu.cpp
* @description Satır içi hücre ekleme ve sütun indeksine göre hücre silme ve erisme islemleri. 
* @course 1.Öğretim A Grubu
* @assignment 1.Ödev
* @date 15.11.2026 (22.11.2026 son güncelleme çalışıyormu diye kontrol edip ufak değişikler yaptım ödevi yollamadan önce)
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/


#include "SatirDugumu.hpp"

SatirDugumu::SatirDugumu() {
    ilkHucre = nullptr;
    sonrakiSatir = nullptr;
}

SatirDugumu::~SatirDugumu() {
    SayiDugumu* aktif = ilkHucre;
    while (aktif != nullptr) {
        SayiDugumu* silinecek = aktif;
        aktif = aktif->getSonraki();
        delete silinecek;
    }
    ilkHucre = nullptr;
}

void SatirDugumu::hucreEkle(int veri) {
    SayiDugumu* yeni = new SayiDugumu(veri);
    if (ilkHucre == nullptr) {
        ilkHucre = yeni;
        return;
    }
    SayiDugumu* aktif = ilkHucre;
    while (aktif->getSonraki() != nullptr) {
        aktif = aktif->getSonraki();
    }
    aktif->setSonraki(yeni);
}

bool SatirDugumu::sutunSil(int sutunIndeks) {
    if (ilkHucre == nullptr || sutunIndeks < 0) {
        return false;
    }
    if (sutunIndeks == 0) {
        SayiDugumu* silinecek = ilkHucre;
        ilkHucre = silinecek->getSonraki();
        delete silinecek;
        return true;
    }
    SayiDugumu* onceki = ilkHucre;
    int i = 0;
    while (onceki != nullptr && i < sutunIndeks - 1) {
        onceki = onceki->getSonraki();
        i++;
    }
    if (onceki == nullptr || onceki->getSonraki() == nullptr) {
        return false;
    }
    SayiDugumu* silinecek = onceki->getSonraki();
    onceki->setSonraki(silinecek->getSonraki());
    delete silinecek;
    return true;
}

SayiDugumu* SatirDugumu::hucreGetir(int sutunIndeks) const {
    if (sutunIndeks < 0) {
        return nullptr;
    }
    SayiDugumu* aktif = ilkHucre;
    int i = 0;
    while (aktif != nullptr && i < sutunIndeks) {
        aktif = aktif->getSonraki();
        i++;
    }
    return aktif;
}

SayiDugumu* SatirDugumu::getIlkHucre() const {
    return ilkHucre;
}

SatirDugumu* SatirDugumu::getSonrakiSatir() const {
    return sonrakiSatir;
}

void SatirDugumu::setSonrakiSatir(SatirDugumu* sonrakiSatir) {
    this->sonrakiSatir = sonrakiSatir;
}