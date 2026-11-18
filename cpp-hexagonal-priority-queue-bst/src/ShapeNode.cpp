/**
* @file Shapenode.cpp
* @description Shapenode'un kaynak dosyası 
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 19.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/
#include "ShapeNode.hpp"

ShapeNode::ShapeNode(Shape* data) {
    this->data = data;
    this->next = nullptr;
}

ShapeNode::~ShapeNode() {
    if (data) {
        delete data;
    }
}