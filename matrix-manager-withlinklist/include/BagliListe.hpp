/** 
* @file BagliListe.hpp
* @description Matris düğümlerini çift yönlü bağlı listede yöneten, sıralama ve dosya işlemlerini yürüten ana liste sınıfı.
* @course 1.Öğretim A Grubu
* @assignment 1.Ödev
* @date 15.11.2026 (düzenlendiği son tarih 22.11.2026)
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#ifndef BAGLILISTE_HPP
#define BAGLILISTE_HPP

#include "MatrisDugumu.hpp"

class BagliListe {
private:
    MatrisDugumu* bas;
    MatrisDugumu* son;
    MatrisDugumu* secili;
    MatrisDugumu* sayfaBasi;
    int dugumSayisi;
    int seciliIndeks;
    char kayitYolu[260];

    void sayfaGuncelle();
    MatrisDugumu* birlestir(MatrisDugumu* sol, MatrisDugumu* sag);
    MatrisDugumu* ortadanBol(MatrisDugumu* kaynak);
    MatrisDugumu* siralaRec(MatrisDugumu* altBas);

public:
    BagliListe();
    ~BagliListe();

    void sonaEkle(Matris* matris);
    void oneEkle(Matris* matris);
    void arkayaEkle(Matris* matris);
    void seciliyiSil();

    void yukariGit();
    void asagiGit();
    void sirala();

    bool dosyadanOku(const char* dosyaAdi);
    bool dosyayaYaz() const;
    void temizle();

    MatrisDugumu* getBas() const;
    MatrisDugumu* getSecili() const;
    MatrisDugumu* getSayfaBasi() const;
    int getDugumSayisi() const;
    int getSeciliIndeks() const;
};

#endif