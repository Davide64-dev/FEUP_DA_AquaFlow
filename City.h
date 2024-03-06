//
// Created by Davide Teixeira on 06/03/2024.
//

#ifndef DA_PROJ1_CITY_H
#define DA_PROJ1_CITY_H

#include <string>

class City {

private:
    std::string name;
    int id;
    std::string code;
    double demand;
    long population;
public:

    City(std::string name, int id, std::string code, double demand, long population);

    std::string getName();
    int getId();
    std::string getCode();
    double getDemand();
    long getPopulation();

};


#endif //DA_PROJ1_CITY_H
