/**
* @file Star.cpp
* @description Star şekli için oluşturulan başlık dosyasının kaynak kodu 
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 19.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/
#include "Star.hpp"

Star::Star(int x, int y, int z, char brush, int s)
    : Shape(x, y, z, brush, 'S') {
    this->size = s;
}

// X Şeklinde Yıldız Çizimi
void Star::draw(char buffer[25][80]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j || i + j == size - 1) {
                int drawY = y + i;
                int drawX = x + j;
                if (drawY >= 0 && drawY < 25 && drawX >= 0 && drawX < 80) {
                    buffer[drawY][drawX] = brush;
                }
            }
        }
    }
}

int Star::getWidth() const { return size; }
int Star::getHeight() const { return size; }