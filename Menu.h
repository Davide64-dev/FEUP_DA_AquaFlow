//
// Created by Davide Teixeira on 05/04/2024.
//

#ifndef DA_PROJ1_MENU_H
#define DA_PROJ1_MENU_H


#include "Manager.h"

class Menu {
private:
    Manager manager;

public:
    Menu(Manager manager);
    void start();
    void printIntro();

    void mainMenu();
    void t21();
};


#endif //DA_PROJ1_MENU_H
