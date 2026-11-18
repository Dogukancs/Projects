/**
* @file MainNode.cpp
* @description Mainnode.hpp nin kaynak kod dosyası
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 18.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#include "MainNode.hpp"

MainNode::MainNode() {
    shapeList = new ShapeList();
    next = nullptr;
    prev = nullptr;
}

MainNode::~MainNode() {
    if (shapeList) {
        delete shapeList;
    }
}