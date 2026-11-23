/** 
* @file KonsolArayuz.cpp
* @description Düğüm kutucukları, matris görünümleri, seçim imleçleri ve klavyeden tuşlarla menü geçişlerinin gerçekleşmesi yani genel olarak arayüz işlemlerinin yapılması için gerekli işlemlerin yapıldığı Arayüz başlık dosyası. 
* @course 1.Öğretim A Grubu
* @assignment 1.Ödev
* @date 15.11.2026 (22.11.2026 son güncelleme)
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#include "KonsolArayuz.hpp"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <conio.h>

using namespace std;

KonsolArayuz::KonsolArayuz(BagliListe* liste) {
    this->liste = liste;
    ekran = nullptr;
    ekranSatir = 0;
    ekranSutun = 0;
}

KonsolArayuz::~KonsolArayuz() {
    ekranSil();
}

void KonsolArayuz::ekranHazirla(int satir, int sutun) {
    if (ekran != nullptr && ekranSatir == satir && ekranSutun == sutun) {
        ekranTemizle();
        return;
    }
    ekranSil();
    ekranSatir = satir;
    ekranSutun = sutun;
    ekran = new char*[ekranSatir];
    for (int i = 0; i < ekranSatir; i++) {
        ekran[i] = new char[ekranSutun + 1];
        memset(ekran[i], ' ', ekranSutun);
        ekran[i][ekranSutun] = '\0';
    }
}

void KonsolArayuz::ekranTemizle() {
    if (ekran == nullptr) {
        return;
    }
    for (int i = 0; i < ekranSatir; i++) {
        memset(ekran[i], ' ', ekranSutun);
        ekran[i][ekranSutun] = '\0';
    }
}

void KonsolArayuz::ekranSil() {
    if (ekran != nullptr) {
        for (int i = 0; i < ekranSatir; i++) {
            delete[] ekran[i];
        }
        delete[] ekran;
        ekran = nullptr;
    }
    ekranSatir = 0;
    ekranSutun = 0;
}

void KonsolArayuz::metinYaz(int x, int y, const char* metin) {
    if (ekran == nullptr || y < 0 || y >= ekranSatir || metin == nullptr) {
        return;
    }
    int uzunluk = (int)strlen(metin);
    for (int i = 0; i < uzunluk; i++) {
        if (x + i >= 0 && x + i < ekranSutun) {
            ekran[y][x + i] = metin[i];
        }
    }
}

void KonsolArayuz::sayiYaz(int x, int y, int sayi) {
    char buf[8];
    sprintf(buf, "%2d", sayi);
    metinYaz(x, y, buf);
}

void KonsolArayuz::kutuCiz(MatrisDugumu* dugum, int y, bool seciliMi) {
    char satirBuf[32];
    char adresBuf[24];

    metinYaz(0, y + 0, "*******************");

    sprintf(adresBuf, "%p", (void*)dugum);
    sprintf(satirBuf, "* %-15s *", adresBuf);
    metinYaz(0, y + 1, satirBuf);

    metinYaz(0, y + 2, "-------------------");

    double ort = dugum->getMatris()->getOrtalama();
    char ortBuf[20];
    sprintf(ortBuf, "%.2f", ort);
    int ortUzunluk = (int)strlen(ortBuf);
    int solBosluk = (17 - ortUzunluk) / 2;
    if (solBosluk < 0) {
        solBosluk = 0;
    }
    int sagBosluk = 17 - ortUzunluk - solBosluk;
    if (sagBosluk < 0) {
        sagBosluk = 0;
    }
    sprintf(satirBuf, "*%*s%s%*s*", solBosluk, "", ortBuf, sagBosluk, "");
    metinYaz(0, y + 3, satirBuf);

    metinYaz(0, y + 4, "-------------------");

    if (dugum->getSonraki() != nullptr) {
        sprintf(adresBuf, "%p", (void*)dugum->getSonraki());
    } else {
        strcpy(adresBuf, "0x0");
    }
    sprintf(satirBuf, "* %-15s *", adresBuf);
    metinYaz(0, y + 5, satirBuf);

    metinYaz(0, y + 6, "*******************");

    if (seciliMi) {
        for (int i = 0; i < 7; i++) {
            metinYaz(21, y + i, "<-");
        }
    }
}

void KonsolArayuz::normalMatrisCiz(Matris* matris, int basX, int basY) {
    if (matris == nullptr || matris->bosMu()) {
        return;
    }
    SatirDugumu* satir = matris->getIlkSatir();
    int r = 0;
    while (satir != nullptr) {
        SayiDugumu* hucre = satir->getIlkHucre();
        int c = 0;
        while (hucre != nullptr) {
            sayiYaz(basX + 1 + c * 3, basY + r, hucre->getVeri());
            hucre = hucre->getSonraki();
            c++;
        }
        satir = satir->getSonrakiSatir();
        r++;
    }
}

void KonsolArayuz::satirSilmeMatrisCiz(Matris* matris, int basX, int basY, int seciliSatir) {
    if (matris == nullptr || matris->bosMu()) {
        return;
    }
    int sutunSay = matris->getSutunSayisi();
    int genislik = sutunSay * 3 + 3;
    char* cizgi = new char[genislik + 1];
    memset(cizgi, '*', genislik);
    cizgi[genislik] = '\0';

    SatirDugumu* satir = matris->getIlkSatir();
    int r = 0;
    int y = basY;

    while (satir != nullptr) {
        if (r == seciliSatir) {
            metinYaz(basX, y, cizgi);
            y++;

            metinYaz(basX, y, "*");
            SayiDugumu* hucre = satir->getIlkHucre();
            int c = 0;
            while (hucre != nullptr) {
                sayiYaz(basX + 2 + c * 3, y, hucre->getVeri());
                hucre = hucre->getSonraki();
                c++;
            }
            metinYaz(basX + genislik - 1, y, "*");
            y++;

            metinYaz(basX, y, cizgi);
            y++;
        } else {
            SayiDugumu* hucre = satir->getIlkHucre();
            int c = 0;
            while (hucre != nullptr) {
                sayiYaz(basX + 2 + c * 3, y, hucre->getVeri());
                hucre = hucre->getSonraki();
                c++;
            }
            y++;
        }
        satir = satir->getSonrakiSatir();
        r++;
    }

    delete[] cizgi;
}

void KonsolArayuz::sutunSilmeMatrisCiz(Matris* matris, int basX, int basY, int seciliSutun) {
    if (matris == nullptr || matris->bosMu()) {
        return;
    }
    int imlecX = basX + seciliSutun * 3;
    metinYaz(imlecX, basY, "|--|");

    SatirDugumu* satir = matris->getIlkSatir();
    int r = 0;
    while (satir != nullptr) {
        int satirY = basY + 1 + r;
        SayiDugumu* hucre = satir->getIlkHucre();
        int c = 0;
        while (hucre != nullptr) {
            int hucreX = basX + c * 3;
            if (c == seciliSutun) {
                metinYaz(hucreX, satirY, "|");
                sayiYaz(hucreX + 1, satirY, hucre->getVeri());
                metinYaz(hucreX + 3, satirY, "|");
            } else {
                sayiYaz(hucreX + 1, satirY, hucre->getVeri());
            }
            hucre = hucre->getSonraki();
            c++;
        }
        satir = satir->getSonrakiSatir();
        r++;
    }

    metinYaz(imlecX, basY + 1 + matris->getSatirSayisi(), "|--|");
}

void KonsolArayuz::anaMenuCiz(int menuX) {
    metinYaz(menuX, 0, "|------- Dugum gezilimi aktif ---------|");
    metinYaz(menuX, 1, "|   w/s tuslari ile gezebilirsiniz     |");
    metinYaz(menuX, 2, "|   q tusu ile one dugum ekle          |");
    metinYaz(menuX, 3, "|   e tusu ile arkaya dugum ekle       |");
    metinYaz(menuX, 4, "|   f tusu ile dugum sec               |");
    metinYaz(menuX, 5, "|   x tusu ile kaydet ve cik           |");
    metinYaz(menuX, 6, "|--------------------------------------|");
}

void KonsolArayuz::islemMenuCiz(int menuX) {
    metinYaz(menuX, 0, "|------- Dugum islemleri aktif --------|");
    metinYaz(menuX, 1, "|   1 Tusu ile Satiri sil              |");
    metinYaz(menuX, 2, "|   2 tusu ile Sutunu sil              |");
    metinYaz(menuX, 3, "|   3 tusu ile Satir ve Sutunu degistir|");
    metinYaz(menuX, 4, "|   x tusu ile dugum gezimine git      |");
    metinYaz(menuX, 5, "|--------------------------------------|");
}

void KonsolArayuz::satirSilMenuCiz(int menuX) {
    metinYaz(menuX, 0, "|------- Satir Silme Aktif ------------|");
    metinYaz(menuX, 1, "|   w/s tuslari ile gezebilirsiniz     |");
    metinYaz(menuX, 2, "|   d tusu ile secili satiri sil       |");
    metinYaz(menuX, 3, "|   x tusu ile dugum gezimine git      |");
    metinYaz(menuX, 4, "|--------------------------------------|");
}

void KonsolArayuz::sutunSilMenuCiz(int menuX) {
    metinYaz(menuX, 0, "|------- Sutun Silme Aktif ------------|");
    metinYaz(menuX, 1, "|   a/d tuslari ile gezebilirsiniz     |");
    metinYaz(menuX, 2, "|   f tusu ile secili sutunu sil       |");
    metinYaz(menuX, 3, "|   x tusu ile dugum gezimine git      |");
    metinYaz(menuX, 4, "|--------------------------------------|");
}

void KonsolArayuz::ciz(int mod, int altSecim) {
    MatrisDugumu* secili = liste->getSecili();
    MatrisDugumu* sayfaBasi = liste->getSayfaBasi();


    int gorunen = 0;
    int seciliSlot = 0;
    MatrisDugumu* gezgin = sayfaBasi;
    while (gezgin != nullptr && gorunen < 5) {
        if (gezgin == secili) {
            seciliSlot = gorunen;
        }
        gezgin = gezgin->getSonraki();
        gorunen++;
    }

    int matrisSatir = 0;
    int matrisSutun = 0;
    if (secili != nullptr && secili->getMatris() != nullptr) {
        matrisSatir = secili->getMatris()->getSatirSayisi();
        matrisSutun = secili->getMatris()->getSutunSayisi();
    }

    int seciliY = 2 + seciliSlot * 8;
    int altCizgiY = (gorunen > 0) ? (2 + gorunen * 8) : 4;
    int matrisBitisY = seciliY + matrisSatir + 4;
    int gerekliSatir = (altCizgiY > matrisBitisY ? altCizgiY : matrisBitisY) + 2;
    if (gerekliSatir < 12) {
        gerekliSatir = 12;
    }

    int matrisBasX = 29;
    int menuX = 52;
    int matrisSag = matrisBasX + matrisSutun * 3 + 6;
    if (matrisSag > menuX) {
        menuX = matrisSag;
    }
    int gerekliSutun = menuX + 42;

    ekranHazirla(gerekliSatir, gerekliSutun);

    metinYaz(0, 0, "-----------------------------------------");

    if (gorunen == 0) {
        metinYaz(0, 2, "Liste bos. 'q' veya 'e' ile dugum ekleyin.");
    } else {
        gezgin = sayfaBasi;
        for (int i = 0; i < gorunen && gezgin != nullptr; i++) {
            kutuCiz(gezgin, 2 + i * 8, gezgin == secili);
            gezgin = gezgin->getSonraki();
        }
    }

    metinYaz(0, altCizgiY, "-----------------------------------------");

    if (secili != nullptr && secili->getMatris() != nullptr) {
        if (mod == 2) {
            satirSilmeMatrisCiz(secili->getMatris(), matrisBasX, seciliY, altSecim);
        } else if (mod == 3) {
            sutunSilmeMatrisCiz(secili->getMatris(), matrisBasX, seciliY, altSecim);
        } else {
            normalMatrisCiz(secili->getMatris(), matrisBasX, seciliY);
        }
    }


    if (mod == 0) {
        anaMenuCiz(menuX);
    } else if (mod == 1) {
        islemMenuCiz(menuX);
    } else if (mod == 2) {
        satirSilMenuCiz(menuX);
    } else if (mod == 3) {
        sutunSilMenuCiz(menuX);
    }

    system("cls");
    for (int i = 0; i < ekranSatir; i++) {
        int sonKarakter = ekranSutun - 1;
        while (sonKarakter >= 0 && ekran[i][sonKarakter] == ' ') {
            sonKarakter--;
        }
        ekran[i][sonKarakter + 1] = '\0';
        cout << ekran[i] << "\n";
    }
    cout.flush();
}


void KonsolArayuz::satirSilMenusu() {
    MatrisDugumu* secili = liste->getSecili();
    if (secili == nullptr || secili->getMatris() == nullptr) {
        return;
    }
    Matris* matris = secili->getMatris();
    int seciliSatir = 0;

    while (true) {
        if (matris->bosMu()) {
            seciliSatir = 0;
        } else if (seciliSatir >= matris->getSatirSayisi()) {
            seciliSatir = matris->getSatirSayisi() - 1;
        }

        ciz(2, seciliSatir);
        char tus = (char)tolower(_getch());

        if (tus == 'w') {
            if (seciliSatir > 0) {
                seciliSatir--;
            }
        } else if (tus == 's') {
            if (!matris->bosMu() && seciliSatir < matris->getSatirSayisi() - 1) {
                seciliSatir++;
            }
        } else if (tus == 'd') {
            if (!matris->bosMu()) {
                matris->satirSil(seciliSatir);
                if (!matris->bosMu() && seciliSatir >= matris->getSatirSayisi()) {
                    seciliSatir = matris->getSatirSayisi() - 1;
                }
            }
        } else if (tus == 'x') {
            if (matris->bosMu()) {
                liste->seciliyiSil();
            } else {
                matris->ortalamaHesapla();
                liste->sirala();
            }
            return;
        }
    }
}


void KonsolArayuz::sutunSilMenusu() {
    MatrisDugumu* secili = liste->getSecili();
    if (secili == nullptr || secili->getMatris() == nullptr) {
        return;
    }
    Matris* matris = secili->getMatris();
    int seciliSutun = 0;

    while (true) {
        if (matris->bosMu()) {
            seciliSutun = 0;
        } else if (seciliSutun >= matris->getSutunSayisi()) {
            seciliSutun = matris->getSutunSayisi() - 1;
        }

        ciz(3, seciliSutun);
        char tus = (char)tolower(_getch());

        if (tus == 'a') {
            if (seciliSutun > 0) {
                seciliSutun--;
            }
        } else if (tus == 'd') {
            if (!matris->bosMu() && seciliSutun < matris->getSutunSayisi() - 1) {
                seciliSutun++;
            }
        } else if (tus == 'f') {
            if (!matris->bosMu()) {
                matris->sutunSil(seciliSutun);
                if (!matris->bosMu() && seciliSutun >= matris->getSutunSayisi()) {
                    seciliSutun = matris->getSutunSayisi() - 1;
                }
            }
        } else if (tus == 'x') {
            if (matris->bosMu()) {
                liste->seciliyiSil();
            } else {
                matris->ortalamaHesapla();
                liste->sirala();
            }
            return;
        }
    }
}


void KonsolArayuz::satirSutunDegistirMenusu() {
    MatrisDugumu* secili = liste->getSecili();
    if (secili == nullptr || secili->getMatris() == nullptr) {
        return;
    }
    Matris* matris = secili->getMatris();
    int satirSay = matris->getSatirSayisi();
    int sutunSay = matris->getSutunSayisi();

    ciz(1, 0);

    if (!matris->kareMi()) {
        cout << "Hata: Matris kare degil (" << satirSay << "x" << sutunSay
             << ")! Satir ve sutun degistirme islemi yapilamaz.\n";
        cout << "Devam etmek icin bir tusa basin...";
        _getch();
        return;
    }

    int satirNo = 0;
    int sutunNo = 0;

    cout << "Degistirilecek satir numarasini girin (1 - " << satirSay << "): ";
    if (!(cin >> satirNo)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Uyari: Gecersiz giris! Bu matris " << satirSay
             << " satir ve " << sutunSay << " sutun icermektedir.\n";
        cout << "Devam etmek icin bir tusa basin...";
        _getch();
        return;
    }

    cout << "Degistirilecek sutun numarasini girin (1 - " << sutunSay << "): ";
    if (!(cin >> sutunNo)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Uyari: Gecersiz giris! Bu matris " << satirSay
             << " satir ve " << sutunSay << " sutun icermektedir.\n";
        cout << "Devam etmek icin bir tusa basin...";
        _getch();
        return;
    }
    cin.ignore(10000, '\n');

    if (satirNo < 1 || satirNo > satirSay || sutunNo < 1 || sutunNo > sutunSay) {
        cout << "Uyari: Gecersiz satir veya sutun numarasi! Bu matris "
             << satirSay << " satir ve " << sutunSay << " sutun icermektedir.\n";
        cout << "Devam etmek icin bir tusa basin...";
        _getch();
        return;
    }

    matris->satirSutunDegistir(satirNo - 1, sutunNo - 1);
}

void KonsolArayuz::islemMenusu() {
    if (liste->getSecili() == nullptr) {
        return;
    }

    while (true) {
        if (liste->getSecili() == nullptr) {
            return;
        }
        ciz(1, 0);
        char tus = (char)tolower(_getch());

        if (tus == '1') {
            satirSilMenusu();
            return;
        } else if (tus == '2') {
            sutunSilMenusu();
            return;
        } else if (tus == '3') {
            satirSutunDegistirMenusu();
            return;
        } else if (tus == 'x') {
            return;
        }
    }
}

void KonsolArayuz::calistir() {
    while (true) {
        ciz(0, 0);
        char tus = (char)tolower(_getch());

        if (tus == 'w') {
            liste->yukariGit();
        } else if (tus == 's') {
            liste->asagiGit();
        } else if (tus == 'q') {
            Matris* yeniMatris = new Matris();
            yeniMatris->rastgeleOlustur();
            liste->oneEkle(yeniMatris);
        } else if (tus == 'e') {
            Matris* yeniMatris = new Matris();
            yeniMatris->rastgeleOlustur();
            liste->arkayaEkle(yeniMatris);
        } else if (tus == 'f') {
            if (liste->getSecili() != nullptr) {
                islemMenusu();
            }
        } else if (tus == 'x') {
            liste->dosyayaYaz();
            break;
        }
    }
}