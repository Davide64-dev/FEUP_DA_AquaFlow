#include "Manager.h"
#include "Menu.h"

int main() {

    int dataset;
    std::cout << "1 - Large DataSet (Continent)" << std::endl;
    std::cout << "2 - Small DataSet (Madeira)" << std::endl;
    std::cout << "Select DataSet: ";
    std::cin >> dataset;

    if (dataset > 2 || dataset < 1) return 0;

    Manager manager = Manager(dataset - 1);

    Menu menu = Menu(manager);

    menu.start();

    return 0;
}
