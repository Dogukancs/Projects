/**
* @file Manager.cpp
* @description Managerın kaynak kod dosyası
* @course 2.Öğretim B
* @assignment 1.Ödev
* @date 20.11.2025
* @author Doğukan Samet Sevindik dogukan.sevindik@ogr.sakarya.edu.tr
*/

#include "Manager.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "Star.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

Manager::Manager() {
    mainList = new MainList();
    isRunning = true;
    srand(time(0));
}

Manager::~Manager() {
    delete mainList;
}

void Manager::generateRandom() {
    // ~20 Ana Düğüm
    int nodeCount = 20; 
    for (int i = 0; i < nodeCount; i++) {
        mainList->addNode();

        MainNode* target = mainList->getHead();
        while(target->next) target = target->next;

        int shapeCount = 2 + rand() % 6; 
        for (int j = 0; j < shapeCount; j++) {
            int typeR = rand() % 3;
            int x = rand() % 70;
            int y = rand() % 20;
            int z = rand() % 10;
            char brush = 33 + rand() % 90;

            Shape* newShape = nullptr;
            if (typeR == 0) { // Rect
                int w = 3 + rand() % 10;
                int h = 3 + rand() % 10;
                newShape = new Rectangle(x, y, z, brush, w, h);
            } else if (typeR == 1) {
                int h = 3 + rand() % 10;
                newShape = new Triangle(x, y, z, brush, h);
            } else { // Star
                int s = 3 + rand() % 8;
                newShape = new Star(x, y, z, brush, s);
            }
            target->shapeList->add(newShape);
        }
    }
}

void Manager::loadFromFile() {
    ifstream file("data.txt");
    if (!file.is_open()) {
        cout << "Dosya bulunamadi, rastgele olusturuluyor..." << endl;
        generateRandom();
        return;
    }

    string line;
    MainNode* currentNode = nullptr;

    while (file >> line) {
        if (line == "NODE") {
            mainList->addNode();
             MainNode* temp = mainList->getHead();
             while(temp->next) temp = temp->next;
             currentNode = temp;
        } else if (line == "RECT") {
            int x, y, z, w, h;
            char brush;
            file >> x >> y >> z >> brush >> w >> h;
            if(currentNode) currentNode->shapeList->add(new Rectangle(x, y, z, brush, w, h));
        } else if (line == "TRI") {
            int x, y, z, h;
            char brush;
            file >> x >> y >> z >> brush >> h;
            if(currentNode) currentNode->shapeList->add(new Triangle(x, y, z, brush, h));
        } else if (line == "STAR") {
            int x, y, z, s;
            char brush;
            file >> x >> y >> z >> brush >> s;
            if(currentNode) currentNode->shapeList->add(new Star(x, y, z, brush, s));
        }
    }
    file.close();
}

void Manager::saveToFile() {
    ofstream file("data.txt");
    if (!file.is_open()) return;

    MainNode* temp = mainList->getHead();
    while (temp) {
        file << "NODE" << endl;
        ShapeNode* sNode = temp->shapeList->getHead();
        while (sNode) {
            Shape* s = sNode->data;
            if (s->getType() == 'R') {
                file << "RECT " << s->getX() << " " << s->getY() << " " << s->getZ() << " " 
                     << s->getBrush() << " " << s->getWidth() << " " << s->getHeight() << endl;
            } else if (s->getType() == 'T') {
                file << "TRI " << s->getX() << " " << s->getY() << " " << s->getZ() << " " 
                     << s->getBrush() << " " << s->getWidth() << endl; // Tri width=height
            } else if (s->getType() == 'S') {
                file << "STAR " << s->getX() << " " << s->getY() << " " << s->getZ() << " " 
                     << s->getBrush() << " " << s->getWidth() << endl;
            }
            sNode = sNode->next;
        }
        temp = temp->next;
    }
    file.close();
}

void Manager::processInput() {
    cout << "Komutlar: [a] Geri, [d] Ileri, [w/s/x/y] Sekil Sec/Tasi (Demo), [q] Cikis" << endl;
    cout << "Secim: ";
    char cmd;
    cin >> cmd;

    if (cmd == 'q') {
        isRunning = false;
    } else if (cmd == 'd') {
        mainList->next();
    } else if (cmd == 'a') {
        mainList->prev();
    } 

    else if (cmd == 'w' || cmd == 's') {
        MainNode* curr = mainList->getCurrent();
        if(curr && curr->shapeList->getHead()) {
            Shape* s = curr->shapeList->getHead()->data;
            if(cmd == 'w') s->setY(s->getY() - 1);
            if(cmd == 's') s->setY(s->getY() + 1);
        }
    }
}

void Manager::run() {
    cout << "1. Rastgele Olustur" << endl;
    cout << "2. Dosyadan Oku" << endl;
    cout << "Secim: ";
    int choice;
    cin >> choice;

    if (choice == 2) loadFromFile();
    else generateRandom();

    while (isRunning) {
        screen.clear();
        screen.render(mainList);
        screen.print();
        processInput();
    }

    saveToFile();
}