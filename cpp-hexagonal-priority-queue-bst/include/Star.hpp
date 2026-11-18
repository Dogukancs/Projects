/**
* @file Star.hpp
* @description Star şekli için oluşturulan sınıfın başlık dosyası, star max boyutu uzunlugu genisligi vb bilgisi tutuluyor.
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 16.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#ifndef STAR_HPP
#define STAR_HPP

#include "Shape.hpp"

class Star : public Shape {
private:
    int size;
public:
    Star(int x, int y, int z, char brush, int s);
    void draw(char buffer[25][80]) override;
    int getWidth() const override;
    int getHeight() const override;
};

#endif