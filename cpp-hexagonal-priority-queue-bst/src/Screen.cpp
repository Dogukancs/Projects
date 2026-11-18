/**
* @file Screen.cpp
* @description Screenin kaynak kod dosyası
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 19.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#include "Screen.hpp"
#include <iostream>
#include <cstdlib> // system("cls")

Screen::Screen() {
    clear();
}

void Screen::clear() {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            buffer[i][j] = ' ';
        }
    }
}

void Screen::sortShapes(Shape** shapes, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (shapes[j]->getZ() > shapes[j + 1]->getZ()) {
                Shape* temp = shapes[j];
                shapes[j] = shapes[j + 1];
                shapes[j + 1] = temp;
            }
        }
    }
}

void Screen::render(MainList* list) {
    MainNode* currNode = list->getCurrent();
    if (!currNode) return;

    ShapeList* shapes = currNode->shapeList;
    int count = shapes->getSize();
    if (count == 0) return;

    // Geçici pointer dizisi oluştur
    Shape** shapeArr = new Shape*[count];
    
    ShapeNode* temp = shapes->getHead();
    int idx = 0;
    while (temp) {
        shapeArr[idx++] = temp->data;
        temp = temp->next;
    }
    sortShapes(shapeArr, count);

    for (int i = 0; i < count; i++) {
        shapeArr[i]->draw(buffer);
    }

    delete[] shapeArr;
}

void Screen::print() {
    system("cls"); 
    
    // Üst sınır
    for(int k=0;k<82;k++) std::cout << "-";
    std::cout << std::endl;

    for (int i = 0; i < 25; i++) {
        std::cout << "|";
        for (int j = 0; j < 80; j++) {
            std::cout << buffer[i][j];
        }
        std::cout << "|" << std::endl;
    }

    for(int k=0;k<82;k++) std::cout << "-";
    std::cout << std::endl;
}