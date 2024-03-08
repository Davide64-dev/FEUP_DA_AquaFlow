//
// Created by Davide Teixeira on 08/03/2024.
//

#include "Manager.h"

Manager::Manager(std::string name) : name(name){
    GraphConstructor constructor = GraphConstructor("../LargeDataSet/Cities.csv",
                                                  "../LargeDataSet/Reservoir.csv",
                                                  "../LargeDataSet/Stations.csv",
                                                  "");
    this->network = constructor.createGraph();

    this->cities = constructor.getCityMap();

    this->reservoirs = constructor.getReservoirMap();

    this->stations = constructor.getStationMap();

}
