/** 
* @file MatrisDugumu.hpp
* @description Ana çift yönlü bağlı listede her bir matrisin taşıyan düğüm yapısı başlık dosyası. 
* @course 1.Öğretim A Grubu
* @assignment 1.Ödev
* @date 15.11.2026 (22.11.2026 son güncelleme)
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#ifndef MATRISDUGUMU_HPP
#define MATRISDUGUMU_HPP

#include "Matris.hpp"

class MatrisDugumu {
private:
    Matris* matris;
    MatrisDugumu* onceki;
    MatrisDugumu* sonraki;

public:
    MatrisDugumu(Matris* matris);
    ~MatrisDugumu();

    Matris* getMatris() const;
    void setMatris(Matris* matris);

    MatrisDugumu* getOnceki() const;
    void setOnceki(MatrisDugumu* onceki);

    MatrisDugumu* getSonraki() const;
    void setSonraki(MatrisDugumu* sonraki);
};

#endif