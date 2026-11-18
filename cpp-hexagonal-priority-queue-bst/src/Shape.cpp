/**
* @file Shape.cpp
* @description Shape sınıfının kaynak kod dosyası
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 18.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#include "Shape.hpp"

Shape::Shape(int x, int y, int z, char brush, char type) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->brush = brush;
    this->type = type;
}

Shape::~Shape() {}

int Shape::getX() const { return x; }
int Shape::getY() const { return y; }
int Shape::getZ() const { return z; }
char Shape::getType() const { return type; }
char Shape::getBrush() const { return brush; }

void Shape::setX(int x) { this->x = x; }
void Shape::setY(int y) { this->y = y; }