//
// Created by Davide Teixeira on 07/03/2024.
//

#ifndef DA_PROJ1_STATION_H
#define DA_PROJ1_STATION_H

#include <string>
#include "Element.h"

class Station : public Element {
private:
    int id;

public:
    Station(std::string code, int id);
    std::string getCode();
    int getId();
};


#endif //DA_PROJ1_STATION_H
