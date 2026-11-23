/** 
* @file BagliListe.cpp
* @description kayitlar.txt den okuma ve oraya yazma, 5 li gösterim sayfada, düğüm ekleme-silme ve ortalamaya göre birleştirmeli sıralamanın yapıldığı kısım.
* @assignment 1.Ödev
* @date 15.11.2026 (22.11.2026 son güncelleme) 
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/


#include "BagliListe.hpp"
#include <fstream>
#include <cstring>

using namespace std;

BagliListe::BagliListe() {
    bas = nullptr;
    son = nullptr;
    secili = nullptr;
    sayfaBasi = nullptr;
    dugumSayisi = 0;
    seciliIndeks = 0;
    strcpy(kayitYolu, "kayitlar.txt");
}

BagliListe::~BagliListe() {
    temizle();
}

void BagliListe::temizle() {
    MatrisDugumu* aktif = bas;
    while (aktif != nullptr) {
        MatrisDugumu* silinecek = aktif;
        aktif = aktif->getSonraki();
        delete silinecek;
    }
    bas = nullptr;
    son = nullptr;
    secili = nullptr;
    sayfaBasi = nullptr;
    dugumSayisi = 0;
    seciliIndeks = 0;
}

void BagliListe::sayfaGuncelle() {
    if (bas == nullptr || secili == nullptr) {
        sayfaBasi = nullptr;
        seciliIndeks = 0;
        return;
    }
    int sayfaIlk = (seciliIndeks / 5) * 5;
    int fark = seciliIndeks - sayfaIlk;
    MatrisDugumu* gezgin = secili;
    for (int i = 0; i < fark && gezgin->getOnceki() != nullptr; i++) {
        gezgin = gezgin->getOnceki();
    }
    sayfaBasi = gezgin;
}

void BagliListe::sonaEkle(Matris* matris) {
    MatrisDugumu* yeni = new MatrisDugumu(matris);
    if (bas == nullptr) {
        bas = yeni;
        son = yeni;
        secili = yeni;
        sayfaBasi = yeni;
        seciliIndeks = 0;
    } else {
        yeni->setOnceki(son);
        son->setSonraki(yeni);
        son = yeni;
    }
    dugumSayisi++;
}

void BagliListe::oneEkle(Matris* matris) {
    if (bas == nullptr || secili == nullptr) {
        sonaEkle(matris);
        return;
    }
    MatrisDugumu* yeni = new MatrisDugumu(matris);
    MatrisDugumu* onc = secili->getOnceki();

    yeni->setSonraki(secili);
    yeni->setOnceki(onc);
    secili->setOnceki(yeni);

    if (onc != nullptr) {
        onc->setSonraki(yeni);
    } else {
        bas = yeni;
    }

    secili = yeni;
    dugumSayisi++;
    sayfaGuncelle();
}

void BagliListe::arkayaEkle(Matris* matris) {
    if (bas == nullptr || secili == nullptr) {
        sonaEkle(matris);
        return;
    }
    MatrisDugumu* yeni = new MatrisDugumu(matris);
    MatrisDugumu* snr = secili->getSonraki();

    yeni->setOnceki(secili);
    yeni->setSonraki(snr);
    secili->setSonraki(yeni);

    if (snr != nullptr) {
        snr->setOnceki(yeni);
    } else {
        son = yeni;
    }

    secili = yeni;
    seciliIndeks++;
    dugumSayisi++;
    sayfaGuncelle();
}

void BagliListe::seciliyiSil() {
    if (secili == nullptr) {
        return;
    }
    MatrisDugumu* silinecek = secili;
    MatrisDugumu* onc = silinecek->getOnceki();
    MatrisDugumu* snr = silinecek->getSonraki();

    if (onc != nullptr) {
        onc->setSonraki(snr);
    } else {
        bas = snr;
    }

    if (snr != nullptr) {
        snr->setOnceki(onc);
    } else {
        son = onc;
    }

    dugumSayisi--;

    if (snr != nullptr) {
        secili = snr;
    } else if (onc != nullptr) {
        secili = onc;
        seciliIndeks--;
    } else {
        secili = nullptr;
        seciliIndeks = 0;
    }

    delete silinecek;
    sayfaGuncelle();
}

void BagliListe::yukariGit() {
    if (secili == nullptr || secili->getOnceki() == nullptr) {
        return;
    }
    secili = secili->getOnceki();
    seciliIndeks--;
    sayfaGuncelle();
}

void BagliListe::asagiGit() {
    if (secili == nullptr || secili->getSonraki() == nullptr) {
        return;
    }
    secili = secili->getSonraki();
    seciliIndeks++;
    sayfaGuncelle();
}

MatrisDugumu* BagliListe::ortadanBol(MatrisDugumu* kaynak) {
    MatrisDugumu* yavas = kaynak;
    MatrisDugumu* hizli = kaynak->getSonraki();
    while (hizli != nullptr && hizli->getSonraki() != nullptr) {
        yavas = yavas->getSonraki();
        hizli = hizli->getSonraki()->getSonraki();
    }
    MatrisDugumu* orta = yavas->getSonraki();
    yavas->setSonraki(nullptr);
    return orta;
}

MatrisDugumu* BagliListe::birlestir(MatrisDugumu* sol, MatrisDugumu* sag) {
    if (sol == nullptr) {
        return sag;
    }
    if (sag == nullptr) {
        return sol;
    }

    MatrisDugumu* baslangic = nullptr;
    if (sol->getMatris()->getOrtalama() <= sag->getMatris()->getOrtalama()) {
        baslangic = sol;
        sol = sol->getSonraki();
    } else {
        baslangic = sag;
        sag = sag->getSonraki();
    }

    MatrisDugumu* kuyruk = baslangic;
    while (sol != nullptr && sag != nullptr) {
        if (sol->getMatris()->getOrtalama() <= sag->getMatris()->getOrtalama()) {
            kuyruk->setSonraki(sol);
            sol = sol->getSonraki();
        } else {
            kuyruk->setSonraki(sag);
            sag = sag->getSonraki();
        }
        kuyruk = kuyruk->getSonraki();
    }

    if (sol != nullptr) {
        kuyruk->setSonraki(sol);
    } else {
        kuyruk->setSonraki(sag);
    }

    return baslangic;
}

MatrisDugumu* BagliListe::siralaRec(MatrisDugumu* altBas) {
    if (altBas == nullptr || altBas->getSonraki() == nullptr) {
        return altBas;
    }
    MatrisDugumu* sag = ortadanBol(altBas);
    MatrisDugumu* sol = siralaRec(altBas);
    sag = siralaRec(sag);
    return birlestir(sol, sag);
}

void BagliListe::sirala() {
    if (bas == nullptr || bas->getSonraki() == nullptr) {
        if (bas != nullptr) {
            secili = bas;
            seciliIndeks = 0;
            sayfaBasi = bas;
        }
        return;
    }

    bas = siralaRec(bas);

    MatrisDugumu* aktif = bas;
    MatrisDugumu* onc = nullptr;
    int indeks = 0;
    while (aktif != nullptr) {
        aktif->setOnceki(onc);
        if (aktif == secili) {
            seciliIndeks = indeks;
        }
        onc = aktif;
        aktif = aktif->getSonraki();
        indeks++;
    }
    son = onc;
    sayfaGuncelle();
}

bool BagliListe::dosyadanOku(const char* dosyaAdi) {
    ifstream dosya(dosyaAdi);
    if (!dosya.is_open()) {
        char altYol[260];
        strcpy(altYol, "../");
        strcat(altYol, dosyaAdi);
        dosya.open(altYol);
        if (!dosya.is_open()) {
            strcpy(kayitYolu, dosyaAdi);
            return false;
        }
        strcpy(kayitYolu, altYol);
    } else {
        strcpy(kayitYolu, dosyaAdi);
    }

    temizle();

    int genislik = 0;
    int yukseklik = 0;
    while (dosya >> genislik >> yukseklik) {
        if (genislik <= 0 || yukseklik <= 0) {
            break;
        }
        Matris* matris = new Matris();
        bool tamam = true;
        for (int r = 0; r < yukseklik; r++) {
            SatirDugumu* satir = new SatirDugumu();
            for (int c = 0; c < genislik; c++) {
                int deger = 0;
                if (!(dosya >> deger)) {
                    tamam = false;
                    break;
                }
                satir->hucreEkle(deger);
            }
            if (!tamam) {
                delete satir;
                break;
            }
            matris->satirEkle(satir);
        }
        if (!tamam) {
            delete matris;
            break;
        }
        matris->setSutunSayisi(genislik);
        matris->ortalamaHesapla();
        sonaEkle(matris);
    }

    dosya.close();

    if (bas != nullptr) {
        sirala();
        secili = bas;
        seciliIndeks = 0;
        sayfaBasi = bas;
    }
    return true;
}

bool BagliListe::dosyayaYaz() const {
    ofstream dosya(kayitYolu, ios::out | ios::trunc);
    if (!dosya.is_open()) {
        return false;
    }

    MatrisDugumu* aktif = bas;
    while (aktif != nullptr) {
        Matris* m = aktif->getMatris();
        if (m != nullptr && !m->bosMu()) {
            dosya << m->getSutunSayisi() << " " << m->getSatirSayisi();
            SatirDugumu* satir = m->getIlkSatir();
            while (satir != nullptr) {
                SayiDugumu* hucre = satir->getIlkHucre();
                while (hucre != nullptr) {
                    dosya << " " << hucre->getVeri();
                    hucre = hucre->getSonraki();
                }
                satir = satir->getSonrakiSatir();
            }
            dosya << "\n";
        }
        aktif = aktif->getSonraki();
    }

    dosya.close();
    return true;
}

MatrisDugumu* BagliListe::getBas() const {
    return bas;
}

MatrisDugumu* BagliListe::getSecili() const {
    return secili;
}

MatrisDugumu* BagliListe::getSayfaBasi() const {
    return sayfaBasi;
}

int BagliListe::getDugumSayisi() const {
    return dugumSayisi;
}

int BagliListe::getSeciliIndeks() const {
    return seciliIndeks;
}