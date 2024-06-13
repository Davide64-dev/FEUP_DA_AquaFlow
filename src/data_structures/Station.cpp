//
// Created by Davide Teixeira on 07/03/2024.
//

#include "Station.h"

Station::Station(std::string code, int id) : Element(code), id(id) {}

std::string Station::getCode() {
    return this->code;
}

int Station::getId() {
    return this->id;
}