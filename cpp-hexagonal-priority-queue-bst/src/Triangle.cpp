/**
* @file Triangle.cpp
* @description Triangle şeklinin sınıfının başlık dosyasının kaynak kodları dosyası
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 19.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/
#include "Triangle.hpp"

Triangle::Triangle(int x, int y, int z, char brush, int h)
    : Shape(x, y, z, brush, 'T') {
    this->height = h;
}

// Dik üçgen çizimi
void Triangle::draw(char buffer[25][80]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= i; j++) {
            int drawY = y + i;
            int drawX = x + j;
            if (drawY >= 0 && drawY < 25 && drawX >= 0 && drawX < 80) {
                buffer[drawY][drawX] = brush;
            }
        }
    }
}

int Triangle::getWidth() const { return height; }
int Triangle::getHeight() const { return height; }