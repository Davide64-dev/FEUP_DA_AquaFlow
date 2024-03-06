//
// Created by Davide Teixeira on 06/03/2024.
//

#ifndef DA_PROJ1_RESERVOIR_H
#define DA_PROJ1_RESERVOIR_H

#include <string>

class Reservoir {
private:
    std::string name;
    std::string municipaly;
    int id;
    std::string code;
    long maximum_delivery;

public:
    Reservoir(std::string name, std::string municipaly, int id, std::string code, long maximum_delivery);
    std::string getName();
    std::string getMunicipaly();
    int getId();
    std::string getCode();
    long getMaximumDelivery();

};


#endif //DA_PROJ1_RESERVOIR_H
