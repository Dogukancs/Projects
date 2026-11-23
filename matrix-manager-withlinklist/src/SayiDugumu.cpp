/** 
* @file SayiDugumu.cpp
* @description SayiDugumu sınıfına ait kurucu , yıkıcı ve erişim metodlarınını içerir. 
* @assignment 1.Ödev
* @date 15.11.2026 (22.11.2026 son güncelleme)
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#include "SayiDugumu.hpp"

SayiDugumu::SayiDugumu(int veri) {
    this->veri = veri;
    this->sonraki = nullptr;
}

SayiDugumu::~SayiDugumu() {
}

int SayiDugumu::getVeri() const {
    return veri;
}

void SayiDugumu::setVeri(int veri) {
    this->veri = veri;
}

SayiDugumu* SayiDugumu::getSonraki() const {
    return sonraki;
}

void SayiDugumu::setSonraki(SayiDugumu* sonraki) {
    this->sonraki = sonraki;
}