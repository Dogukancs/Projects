/**
* @file Mainlist.cpp
* @description Mainlist.hpp nin kaynak kod dosyası
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 18.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/


#include "MainList.hpp"

MainList::MainList() {
    head = nullptr;
    tail = nullptr;
    current = nullptr;
}

MainList::~MainList() {
    MainNode* tmp = head;
    while (tmp) {
        MainNode* next = tmp->next;
        delete tmp;
        tmp = next;
    }
}

void MainList::addNode() {
    MainNode* newNode = new MainNode();
    addNode(newNode);
}

void MainList::addNode(MainNode* newNode) {
    if (!head) {
        head = newNode;
        tail = newNode;
        current = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void MainList::next() {
    if (current && current->next) {
        current = current->next;
    }
}

void MainList::prev() {
    if (current && current->prev) {
        current = current->prev;
    }
}

MainNode* MainList::getCurrent() const {
    return current;
}

MainNode* MainList::getHead() const {
    return head;
}