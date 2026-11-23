/** 
* @file SayiDugumu.hpp
* @description Matrislerin hücrelerindeki çift haneli sayıları tuttuğum düğüm sınıfı tanımı.
* @course 1.Öğretim A Grubu
* @assignment 1.Ödev
* @date 15.11.2026 (son güncelleme 22.11.2026) 
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#ifndef SAYIDUGUMU_HPP
#define SAYIDUGUMU_HPP

class SayiDugumu {
private:
    int veri;
    SayiDugumu* sonraki;

public:
    SayiDugumu(int veri);
    ~SayiDugumu();


    int getVeri() const;
    void setVeri(int veri);


    SayiDugumu* getSonraki() const;
    void setSonraki(SayiDugumu* sonraki);

};

#endif

