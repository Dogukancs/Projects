/**
* @file Shapelist.cpp
* @description Shapelist'in kaynak kod dosyası 
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 19.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#include "ShapeList.hpp"

ShapeList::ShapeList() {
    head = nullptr;
}

ShapeList::~ShapeList() {
    ShapeNode* tmp = head;
    while (tmp) {
        ShapeNode* next = tmp->next;
        delete tmp;
        tmp = next;
    }
}

void ShapeList::add(Shape* shape) {
    ShapeNode* newNode = new ShapeNode(shape);
    if (!head) {
        head = newNode;
    } else {
        ShapeNode* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void ShapeList::remove(Shape* shape) {
    if (!head) return;

    if (head->data == shape) {
        ShapeNode* temp = head;
        head = head->next;
        temp->next = nullptr; 
        delete temp;
        return;
    }

    ShapeNode* current = head;
    while (current->next && current->next->data != shape) {
        current = current->next;
    }

    if (current->next) {
        ShapeNode* toDelete = current->next;
        current->next = toDelete->next;
        toDelete->next = nullptr;
        delete toDelete;
    }
}

ShapeNode* ShapeList::getHead() const {
    return head;
}

int ShapeList::getSize() const {
    int count = 0;
    ShapeNode* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}