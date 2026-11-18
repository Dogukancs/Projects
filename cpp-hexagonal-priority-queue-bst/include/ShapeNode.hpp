/**
* @file Shapenode.hpp
* @description Shapenode'un başlık dosyası
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 16.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#ifndef SHAPENODE_HPP
#define SHAPENODE_HPP

#include "Shape.hpp"

class ShapeNode {
public:
    Shape* data;
    ShapeNode* next;

    ShapeNode(Shape* data);
    ~ShapeNode();
};

#endif