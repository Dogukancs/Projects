/** 
* @file MatrisDugumu.cpp
* @description MatrisDugumu sınıfının işaretçi yönetimi ve bellek temizleme metodlarını içeren kısım. 
* @course 1.Öğretim A Grubu
* @assignment 1.Ödev
* @date 15.11.2026 (22.11.2026 son güncelleme)
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#include "MatrisDugumu.hpp"

MatrisDugumu::MatrisDugumu(Matris* matris) {
    this->matris = matris;
    onceki = nullptr;
    sonraki = nullptr;
}

MatrisDugumu::~MatrisDugumu() {
    if (matris != nullptr) {
        delete matris;
        matris = nullptr;
    }
}

Matris* MatrisDugumu::getMatris() const {
    return matris;
}

void MatrisDugumu::setMatris(Matris* matris) {
    this->matris = matris;
}

MatrisDugumu* MatrisDugumu::getOnceki() const {
    return onceki;
}

void MatrisDugumu::setOnceki(MatrisDugumu* onceki) {
    this->onceki = onceki;
}

MatrisDugumu* MatrisDugumu::getSonraki() const {
    return sonraki;
}

void MatrisDugumu::setSonraki(MatrisDugumu* sonraki) {
    this->sonraki = sonraki;
}