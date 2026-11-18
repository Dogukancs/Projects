/**
* @file Shapelist.hpp
* @description Shapelist'in başlık dosyası, şekiller için oluşturulan shapelist içinde node ekleme silme boyutunu ögrenme başa gitme vb.
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 16.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/
#ifndef SHAPELIST_HPP
#define SHAPELIST_HPP

#include "ShapeNode.hpp"

class ShapeList {
private:
    ShapeNode* head;
public:
    ShapeList();
    ~ShapeList();
    
    void add(Shape* shape);
    void remove(Shape* shape);
    ShapeNode* getHead() const;
    int getSize() const;
};

#endif