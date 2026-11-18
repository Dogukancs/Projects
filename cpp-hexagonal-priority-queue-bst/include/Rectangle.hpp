/**
* @file Rectangle.hpp
* @description Rectangleın başlık dosyası, rectangle sınıfı şekillerden biri max boyutu uzunlugu genisligi vb bilgisi tutuluyor.
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 16.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/


#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Shape.hpp"

class Rectangle : public Shape {
private:
    int width;
    int height;
public:
    Rectangle(int x, int y, int z, char brush, int w, int h);
    void draw(char buffer[25][80]) override;
    int getWidth() const override;
    int getHeight() const override;
};

#endif