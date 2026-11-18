/**
* @file MainNode.hpp
* @description Mainnode un başlık dosyası, mainnode a shapelistin verilmesi 
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 16.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/
#ifndef MAINNODE_HPP
#define MAINNODE_HPP

#include "ShapeList.hpp"

class MainNode {
public:
    ShapeList* shapeList;
    MainNode* next;
    MainNode* prev;

    MainNode();
    ~MainNode();
};

#endif