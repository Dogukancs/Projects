/**
* @file Triangle.hpp
* @description Triangle şeklinin sınıfının başlık dosyası, triangle max boyutu uzunlugu genisligi vb bilgisi tutuluyor.
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 16.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Shape.hpp"

class Triangle : public Shape {
private:
    int height;
public:
    Triangle(int x, int y, int z, char brush, int h);
    void draw(char buffer[25][80]) override;
    int getWidth() const override;
    int getHeight() const override;
};

#endif