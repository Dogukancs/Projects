/** 
* @file Matris.cpp
* @description Rastgele tekrarsız matris sayılarının üretimi , satır-sütun silme, kare matris kontrolü ve ona göre yerdeğiştirme ve aritmetik ortalama hesabı bu kısımda.
* @assignment 1.Ödev
* @date 15.11.2026 (22.11.2026 son güncelleme)
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#include "Matris.hpp"
#include <cstdlib>

using namespace std;

Matris::Matris() {
    ilkSatir = nullptr;
    sonSatir = nullptr;
    satirSayisi = 0;
    sutunSayisi = 0;
    ortalama = 0.0;
}

Matris::~Matris() {
    SatirDugumu* aktif = ilkSatir;
    while (aktif != nullptr) {
        SatirDugumu* silinecek = aktif;
        aktif = aktif->getSonrakiSatir();
        delete silinecek;
    }
    ilkSatir = nullptr;
    sonSatir = nullptr;
    satirSayisi = 0;
    sutunSayisi = 0;
}

void Matris::satirEkle(SatirDugumu* yeniSatir) {
    yeniSatir->setSonrakiSatir(nullptr);
    if (ilkSatir == nullptr) {
        ilkSatir = yeniSatir;
        sonSatir = yeniSatir;
    } else {
        sonSatir->setSonrakiSatir(yeniSatir);
        sonSatir = yeniSatir;
    }
    satirSayisi++;
}

void Matris::rastgeleOlustur() {
    int boyut = 3 + (rand() % 7);

    int sayilar[100];
    for (int i = 0; i < 100; i++) {
        sayilar[i] = i;
    }
    for (int i = 99; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = sayilar[i];
        sayilar[i] = sayilar[j];
        sayilar[j] = tmp;
    }

    int k = 0;
    for (int r = 0; r < boyut; r++) {
        SatirDugumu* yeniSatir = new SatirDugumu();
        for (int c = 0; c < boyut; c++) {
            yeniSatir->hucreEkle(sayilar[k]);
            k++;
        }
        satirEkle(yeniSatir);
    }
    sutunSayisi = boyut;
    ortalamaHesapla();
}

bool Matris::satirSil(int satirIndeks) {
    if (ilkSatir == nullptr || satirIndeks < 0 || satirIndeks >= satirSayisi) {
        return false;
    }
    SatirDugumu* silinecek = nullptr;
    if (satirIndeks == 0) {
        silinecek = ilkSatir;
        ilkSatir = silinecek->getSonrakiSatir();
        if (ilkSatir == nullptr) {
            sonSatir = nullptr;
        }
    } else {
        SatirDugumu* onceki = ilkSatir;
        for (int i = 0; i < satirIndeks - 1; i++) {
            onceki = onceki->getSonrakiSatir();
        }
        silinecek = onceki->getSonrakiSatir();
        onceki->setSonrakiSatir(silinecek->getSonrakiSatir());
        if (silinecek == sonSatir) {
            sonSatir = onceki;
        }
    }
    delete silinecek;
    satirSayisi--;
    if (satirSayisi == 0) {
        sutunSayisi = 0;
    }
    return true;
}

bool Matris::sutunSil(int sutunIndeks) {
    if (ilkSatir == nullptr || sutunIndeks < 0 || sutunIndeks >= sutunSayisi) {
        return false;
    }
    SatirDugumu* aktif = ilkSatir;
    while (aktif != nullptr) {
        aktif->sutunSil(sutunIndeks);
        aktif = aktif->getSonrakiSatir();
    }
    sutunSayisi--;
    if (sutunSayisi == 0) {
        SatirDugumu* s = ilkSatir;
        while (s != nullptr) {
            SatirDugumu* sil = s;
            s = s->getSonrakiSatir();
            delete sil;
        }
        ilkSatir = nullptr;
        sonSatir = nullptr;
        satirSayisi = 0;
    }
    return true;
}

bool Matris::satirSutunDegistir(int satirIndeks, int sutunIndeks) {
    if (!kareMi()) {
        return false;
    }
    if (satirIndeks < 0 || satirIndeks >= satirSayisi ||
        sutunIndeks < 0 || sutunIndeks >= sutunSayisi) {
        return false;
    }
    SatirDugumu* hedefSatir = satirGetir(satirIndeks);
    if (hedefSatir == nullptr) {
        return false;
    }

    SatirDugumu* satirGezgin = ilkSatir;
    SayiDugumu* yatayHucre = hedefSatir->getIlkHucre();

    for (int k = 0; k < satirSayisi; k++) {
        if (satirGezgin == nullptr || yatayHucre == nullptr) {
            break;
        }
        SayiDugumu* dikeyHucre = satirGezgin->hucreGetir(sutunIndeks);
        if (dikeyHucre != nullptr) {
            int tmp = yatayHucre->getVeri();
            yatayHucre->setVeri(dikeyHucre->getVeri());
            dikeyHucre->setVeri(tmp);
        }
        satirGezgin = satirGezgin->getSonrakiSatir();
        yatayHucre = yatayHucre->getSonraki();
    }
    return true;
}

void Matris::ortalamaHesapla() {
    if (satirSayisi <= 0 || sutunSayisi <= 0) {
        ortalama = 0.0;
        return;
    }
    long long toplam = 0;
    long long adet = 0;
    SatirDugumu* satir = ilkSatir;
    while (satir != nullptr) {
        SayiDugumu* hucre = satir->getIlkHucre();
        while (hucre != nullptr) {
            toplam += hucre->getVeri();
            adet++;
            hucre = hucre->getSonraki();
        }
        satir = satir->getSonrakiSatir();
    }
    if (adet == 0) {
        ortalama = 0.0;
    } else {
        ortalama = (double)toplam / adet;
    }
}

SatirDugumu* Matris::satirGetir(int satirIndeks) const {
    if (satirIndeks < 0 || satirIndeks >= satirSayisi) {
        return nullptr;
    }
    SatirDugumu* aktif = ilkSatir;
    for (int i = 0; i < satirIndeks && aktif != nullptr; i++) {
        aktif = aktif->getSonrakiSatir();
    }
    return aktif;
}

int Matris::degerGetir(int satirIndeks, int sutunIndeks) const {
    SatirDugumu* satir = satirGetir(satirIndeks);
    if (satir == nullptr) {
        return 0;
    }
    SayiDugumu* hucre = satir->hucreGetir(sutunIndeks);
    if (hucre == nullptr) {
        return 0;
    }
    return hucre->getVeri();
}

bool Matris::bosMu() const {
    return (satirSayisi <= 0 || sutunSayisi <= 0 || ilkSatir == nullptr);
}

bool Matris::kareMi() const {
    return (satirSayisi > 0 && satirSayisi == sutunSayisi);
}

SatirDugumu* Matris::getIlkSatir() const {
    return ilkSatir;
}

int Matris::getSatirSayisi() const {
    return satirSayisi;
}

int Matris::getSutunSayisi() const {
    return sutunSayisi;
}

void Matris::setSutunSayisi(int sutunSayisi) {
    this->sutunSayisi = sutunSayisi;
}

double Matris::getOrtalama() const {
    return ortalama;
}