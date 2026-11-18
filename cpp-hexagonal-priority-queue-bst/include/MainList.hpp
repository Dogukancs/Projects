/**
* @file Mainlist.hpp
* @description Mainlistin başlık dosyası, mainliste node ekleme ileri geri gibi işlemler 
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 16.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#ifndef MAINLIST_HPP
#define MAINLIST_HPP

#include "MainNode.hpp"

class MainList {
private:
    MainNode* head;
    MainNode* tail;
    MainNode* current; 

public:
    MainList();
    ~MainList();

    void addNode(); 
    void addNode(MainNode* newNode);
    
    void next();
    void prev();
    
    MainNode* getCurrent() const;
    MainNode* getHead() const;
};

#endif