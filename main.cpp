#include <iostream>
#include <filesystem>
#include "data_structures/City.h"
#include "Manager.h"
#include "Menu.h"

int main() {

    Manager manager = Manager();

    Menu menu = Menu(manager);

    menu.start();
}
