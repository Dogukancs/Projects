/**
* @file Shape.hpp
* @description Shape sınıfının başlık dosyası, shape oluşturma özellikler ve koordinatları alınıyor.
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 16.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#ifndef SHAPE_HPP
#define SHAPE_HPP

class Shape {
protected:
    int x, y;
    int z;
    char brush;
    char type; // 'R', 'T', 'S'

public:
    Shape(int x, int y, int z, char brush, char type);
    virtual ~Shape();

    int getX() const;
    int getY() const;
    int getZ() const;
    char getType() const;
    char getBrush() const;

    void setX(int x);
    void setY(int y);

    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    
    virtual void draw(char buffer[25][80]) = 0;
};

#endif