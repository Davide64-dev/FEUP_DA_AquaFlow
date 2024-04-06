#include "Manager.h"
#include "Menu.h"

int main() {

    Manager manager = Manager();

    Menu menu = Menu(manager);

    menu.start();

    return 0;
}
