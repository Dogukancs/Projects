/**
* @file Screen.hpp
* @description Screenin başlık dosyası, ekranda sekillerin gözükmesiyle ilgili kısım sekilleri sıralama işlemide yapılıyo.
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 16.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "MainList.hpp"

class Screen {
private:
    char buffer[25][80];
    void sortShapes(Shape** shapes, int count);

public:
    Screen();
    void clear();
    void render(MainList* list);
    void print();
};

#endif