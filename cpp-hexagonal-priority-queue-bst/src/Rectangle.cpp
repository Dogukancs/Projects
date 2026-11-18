/**
* @file Rectangle.cpp
* @description Rectangleın kaynak kod dosyası
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 18.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#include "Rectangle.hpp"

Rectangle::Rectangle(int x, int y, int z, char brush, int w, int h) 
    : Shape(x, y, z, brush, 'R') {
    this->width = w;
    this->height = h;
}

void Rectangle::draw(char buffer[25][80]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int drawY = y + i;
            int drawX = x + j;
            if (drawY >= 0 && drawY < 25 && drawX >= 0 && drawX < 80) {
                buffer[drawY][drawX] = brush;
            }
        }
    }
}

int Rectangle::getWidth() const { return width; }
int Rectangle::getHeight() const { return height; }