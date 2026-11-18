/**
* @file Manager.hpp
* @description Managerın başlık dosyası, çeşitli işlemlerin yapılabilmesi için oluşturuldu
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 17.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "MainList.hpp"
#include "Screen.hpp"

class Manager {
private:
    MainList* mainList;
    Screen screen;
    bool isRunning;

    // Yardımcılar
    void generateRandom();
    void loadFromFile();
    void saveToFile();
    void processInput();

public:
    Manager();
    ~Manager();
    void run();
};

#endif